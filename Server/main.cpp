#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iostream>
#include<string>
#include<boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

string make_daytime_string() {
	time_t now = time(0);//시간정보 초기화('time_t'는 time()함수의 반환형)
	return ctime(&now);//문자열 형태로 서버 컴퓨터의 날짜 및 시간정보 반환
}

int main()
{
	try {
		boost::asio::io_service io_service;//(0)IO Service 객체 생성
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));//(1)13번 포트로 연결받는 수동 포켓 생성
		while (1)
		{
			tcp::socket socket(io_service);
			acceptor.accept(socket);//(2)클라이언트 소켓 생성 후, 연결을 기다림
			string message = make_daytime_string();//make_daytime_string()함수를 이용해 보낼 메시지 생성
			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);//(3)메시지를 버퍼에 담아 전송
		}
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
	}
	return 0;
}