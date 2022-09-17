# web_analiticscpp
c++ cording web analitics(simple)

## セットアップ
[json.hpp](https://github.com/nlohmann/json)をincludeに追加  
普通にgcc等でコンパイルこの時-o war.cgiで書きだすとよい  
そしたらwar.cgiをcgi-binに追加(ほかのところの場合jsの中のアクセス先を変更)  
そしてwar.jsをドキュメントルート等に配置し適切なパスをhtmlファイル内に書くex(<script defer src='/war.js'></script>)

## compile and setup

it need [json.hpp](https://github.com/nlohmann/json) library to compile cpp sorces.  
I think result binary name should change to war.cgi and set to cgi-bin folder.  
and set war.js on your root http document and add on html file as <script defer src='/war.js'></script>
received results save as analytics_data.csv on same folder which war.cgi.  
