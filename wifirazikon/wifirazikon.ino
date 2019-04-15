#include <ESP8266WiFi.h>                         //ESP8266WiFiライブラリ
#include <ESP8266WebServer.h>                    //ESP8266Webサーバーライブラリ
#include <FS.h>　　　　　　　　　　　             //ファイルシステムSPIFFSライブラリ

// パスワードは英数字8文字(必ず8文字)
const char *ssid        = "wifi-car";             //SSIDを控えておいてください
const char *password    = "wifi-car";             //パスワードを控えておいてください

const char *path_root   = "/index.html";          //コントローラー画面表示HTMLファイルの場所を指定
uint8_t buf[16384];                               //ファイル格納バッファサイズを指定
/*
*/
const int PIN1 = 4;                             //右前進
const int PIN2 = 5;                             //右後進
const int PIN3 = 12;                            //左前進
const int PIN4 = 13;                            //左後進
const int LPIN = 14;                            //LPIN

ESP8266WebServer server(80);                    //HTTPサーバーの設定


//HTMLファイル送出
void handleRoot() {
  server.send(200, "text/html", (char *)buf);     //HTTPステータスコード200（OK）＋タイプHTML　HTMLファイル送出
}

//左回転
void LTS() {
  digitalWrite(PIN1, HIGH);
  digitalWrite(PIN2, LOW);
  digitalWrite(PIN3, LOW);
  digitalWrite(PIN4, HIGH);
  server.send(200, "text/html", "LTS");   //HTTPステータスコード200（OK）＋タイプHTML　メッセージ送出
}

//右回転
void RTS() {
  digitalWrite(PIN1, LOW);
  digitalWrite(PIN2, HIGH);
  digitalWrite(PIN3, HIGH);
  digitalWrite(PIN4, LOW);
  server.send(200, "text/html", "RTS");
}

//前進
void GOS() {
  digitalWrite(PIN1, HIGH);
  digitalWrite(PIN2, LOW);
  digitalWrite(PIN3, HIGH);
  digitalWrite(PIN4, LOW);
  server.send(200, "text/html", "GO");
}

//右前進
void LES() {
  digitalWrite(PIN1, LOW);
  digitalWrite(PIN2, LOW);
  digitalWrite(PIN3, HIGH);
  digitalWrite(PIN4, LOW);
  server.send(200, "text/html", "LES");
}

//停止
void STS() {
  digitalWrite(PIN1, LOW);
  digitalWrite(PIN2, LOW);
  digitalWrite(PIN3, LOW);
  digitalWrite(PIN4, LOW);
  server.send(200, "text/html", "STS");
}

//左前進
void RIS() {
  digitalWrite(PIN1, HIGH);
  digitalWrite(PIN2, LOW);
  digitalWrite(PIN3, LOW);
  digitalWrite(PIN4, LOW);
  server.send(200, "text/html", "RIS");
}

//予備1
void AZS() {
  digitalWrite(PIN1, HIGH);
  digitalWrite(PIN2, HIGH);
  digitalWrite(PIN3, LOW);
  digitalWrite(PIN4, LOW);
  server.send(200, "text/html", "AZS");
}

//後進
void BBS() {
  digitalWrite(PIN1, LOW);
  digitalWrite(PIN2, HIGH);
  digitalWrite(PIN3, LOW);
  digitalWrite(PIN4, HIGH);
  server.send(200, "text/html", "BBS");
}

//予備2
void ZAS() {
  digitalWrite(PIN1, LOW);
  digitalWrite(PIN2, LOW);
  digitalWrite(PIN3, HIGH);
  digitalWrite(PIN4, HIGH);
  server.send(200, "text/html", "ZAS");
}




void setup() {
  delay(1000);
  pinMode(LPIN, OUTPUT);                         //LeｄPinをデジタル出力モードに設定
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
  pinMode(PIN3, OUTPUT);
  pinMode(PIN4, OUTPUT);
  

  SPIFFS.begin();                                  //ファイルシステム起動
  File htmlFile = SPIFFS.open(path_root, "r");     //読み込みモードで、paht_rootで指定したindex.htmlファイルを開く
  size_t size = htmlFile.size();                  //ファイルの大きさを取得
  htmlFile.read(buf, size);                        //ファイル収納バッファに読み込む
  htmlFile.close();                                //ファイルを閉じる

  WiFi.softAP(ssid, password);                    //設定されたSSID・パスワードでWiFiアクセスモード起動
  IPAddress myIP = WiFi.softAPIP();
  delay(500);

  server.on("/", handleRoot);                      //「/」を受信した時に呼び出す関数の設定
  server.on("/LT/", LTS);
  server.on("/RT/", RTS);
  server.on("/GO/", GOS);

  server.on("/LE/", LES);
  server.on("/ST/", STS);
  server.on("/RI/", RIS);

  server.on("/AZ/",AZS);
  server.on("/BB/",BBS);
  server.on("/ZA/", ZAS);

  server.begin();                                  //HTTPサーバー起動
  digitalWrite(LPIN, HIGH);                      //Ledを点灯
}

void loop() {
  server.handleClient();                           //送信されてきた内容の確認
}
