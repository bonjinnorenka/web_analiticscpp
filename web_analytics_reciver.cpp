#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <chrono>

#include "json.hpp"

using json = nlohmann::json;

void return_json(json jsondata){
    std::cout << "Content-Type: application/json";
    std::cout << "\nCache-Control: no-cache";
    std::cout << "\n\n";
    std::cout << jsondata.dump() << std::endl;
    exit(1);
}

std::string deleteNl2(std::string targetStr){
	const char CR = '\r';
	const char LF = '\n';
	std::string destStr;
	for (const auto c : targetStr) {
		if (c != CR && c != LF) {
			destStr += c;
		}
	}
	targetStr = std::move(destStr);
    return targetStr;
}

int main(){
    json res_js;//返信用jsonを定義
    res_js["plang"] = "c++";
    bool debug = true;
    if ((std::string)std::getenv("REQUEST_METHOD")==(std::string)"POST"||debug){
        //変数定義
        std::string origin,access_code,ip,referrer,message,filepath,useragent;
        int statuscode = 200;
        int speed = 0;
        try{
            std::string receive_jsstring;
            std::cin >> receive_jsstring;
            //jsonをパース
            json receive_json = json::parse(receive_jsstring);
            origin = (std::string)receive_json["origin"];
            ip = (std::string)std::getenv("REMOTE_ADDR");
            referrer = (std::string)receive_json["referrer"];
            statuscode = (int)receive_json["statuscode"];
            speed = (int)receive_json["speed_ms"];
            message = (std::string)receive_json["message"];
            access_code = (std::string)receive_json["access_code"];
            filepath = (std::string)receive_json["filepath"];
            useragent = (std::string)std::getenv("HTTP_USER_AGENT");
        }
        catch(int ercode){
            res_js["status"] = "error";
            res_js["ermessage"] = "json parse error";
            return_json(res_js);
        }
        //こっから保存
        std::ofstream ofs("analytics_data.csv",std::ios::app);
        auto now = std::chrono::system_clock::now();
        std::time_t end_time = std::chrono::system_clock::to_time_t(now);
        std::string writetxt = deleteNl2((std::string)std::ctime(&end_time)) + "," + origin + "," + filepath + "," + useragent + "," + ip + "," + referrer + "," + std::to_string(statuscode) + "," + message + "," + access_code + "," + std::to_string(speed);
        ofs << writetxt << std::endl;
        ofs.close();
        res_js["status"] = "success";
        res_js["access_code"] = access_code;
        return_json(res_js);
    }
}
