/**
 * @file simple_http_server.hpp
 * @brief a simple http server
 *
 */

#ifndef _SIMPLE_HTTP_HPP_
#define _SIMPLE_HTTP_HPP_

#endif  // _SIMPLE_HTTP_HPP_
#include<iostream>
#include<pthread.h>
#include<functional>
#include<string>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>

using namespace std;
typedef function<void (string& req,string* resp)> Handler;
class TcpSocket{
 public:
    TcpSocket():_fd(-1){}
    TcpSocket(int fd):_fd(fd){}

    bool Socket(){
        _fd = socket(AF_INET,SOCK_STREAM,0);
        if(_fd < 0){
            cerr<<"socket";
            return false;
        }
        clog<<"open fd = "<<_fd<<endl;
        return true;
    }
    bool Close()const{
        close(_fd);
        clog<<"close fd = "<<_fd<<endl;
        return true;
    }

    bool Bind(const string& ip, uint16_t port)const
    {
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_port = htons(port);

        int ret = bind(_fd,(sockaddr*)&addr, sizeof(addr));
        if(ret < 0){
            cerr<<"bind false";
            return false;
        } 
        clog<<"bind success"<<endl;
        return true;
    }

    bool Listen(int num) const
    {
        int ret = listen(_fd, num);
        if(ret < 0)
        {
            cerr<<"listen false";
            return false;
        }
        clog<<"listen true"<<endl;
        return true;
    }
    bool Accept(TcpSocket* peer, string* ip = NULL, uint16_t* port = NULL)const
    {
        sockaddr_in peer_addr;
        socklen_t len = sizeof(peer_addr);
        int new_sock = accept(_fd,(sockaddr*)&peer_addr,&len);
        if(new_sock < 0){
            cerr<<"accept false";
            return false;
        }
        clog<<"accept fd= "<<new_sock<<endl;
        peer->_fd = new_sock;
        if(ip!=NULL)
        {
            *ip = inet_ntoa(peer_addr.sin_addr);
        }
        if(port!=NULL)
        {
            *port = ntohs(peer_addr.sin_port);
        }
        return true;
    }

    bool Recv(string* buf) const
    {
        buf->clear();
        char tmp[1024*10] = {0};
        ssize_t read_size = recv(_fd, tmp, sizeof(tmp),0);
        if(read_size < 0){
            cerr<<"recv false";
            return false;
        }
        if(read_size == 0)
        return false;

        buf->assign(tmp,read_size);
        return true;
    }

    bool Send(string& buf)const
    {
        ssize_t write_size = send(_fd,buf.data(),buf.size(),0);
        if(write_size < 0)
        {
            cerr<<"send false";
            return false;
        }
        return true;
    }

    bool Connect(string& ip, uint16_t port)
    {
        sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        addr.sin_port = htons(port);
        int ret = connect(_fd,(sockaddr*)&addr, sizeof(addr));
         
        if(ret < 0){
            cerr<<"connect false";
            return false;
        }
        return true;
    }

    int GetFd()const
    {
        return _fd;
    }
 private:
    int _fd;
};
struct Arg{
  TcpSocket new_sock;
  string ip;
  uint16_t port;
  Handler handler;
};
class TcpPthreadServer
{
public:
  TcpPthreadServer(const string& ip, uint16_t port):_ip(ip),_port(port){}

  bool Start(Handler handler)
  {
    //1.创建socket
    listen_sock.Socket();
    //2.绑定ip 端口号
    listen_sock.Bind(_ip,_port);
    //3.监听
    listen_sock.Listen(5);
    //4.进入事件主循环
    while(1)
    {
      //5.进行accept
      Arg* arg = new Arg(); 
      arg->handler = handler;
      if(!listen_sock.Accept(&arg->new_sock,&arg->ip,&arg->port)){
        continue;
      }
      cout<<"["<<arg->ip<<":"<<arg->port<<"]"<<"客户端已连接"<<endl;
      //6.创建线程
      pthread_t tid;
      pthread_create(&tid,NULL,ThreadEntry,arg);
      pthread_detach(tid);
    }
    return true;

  }
  static void* ThreadEntry(void* arg)
  {
    Arg* Targ = (Arg*)arg;
    while(1)
    {
      //1.读取请求
      string req;
      bool ret = Targ->new_sock.Recv(&req);
      if(!ret){ 
        cout<<"["<<Targ->ip<<":"<<Targ->port<<"]"<<"客户端已断开连接"<<endl;
        break;
      }  
      cout<<"["<<Targ->ip<<":"<<Targ->port<<"]"<<endl<<"req: "<<endl<<req<<endl;
      //2.根据请求计算响应
      string resp;
      Targ->handler(req,&resp);
      //3.发送响应
      Targ->new_sock.Send(resp);
      cout<<"resp: "<<endl<<resp<<endl;
    }
    Targ->new_sock.Close();
    Targ = nullptr;
    return nullptr;
  }
private:
  TcpSocket listen_sock;
  string _ip;
  uint16_t _port;
};
