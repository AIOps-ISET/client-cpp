#include "simple_http_server.hpp"
#include<string>
using namespace std;
void HttpProcess(string& req, string* resp)
{
 string first_line = "HTTP/1.0 200 OK\n";
 string body = "<html><div><h1>hello world</h1></div></html\n";
  string header = "Content-Type: text/html\ncharset: gbk\nContent-Length:"
            +to_string(body.size())+"\n\n";
 *resp = first_line + header + body;
 //service firewalld stop 关闭防火墙 #centos 7
 //service firewalld status
}