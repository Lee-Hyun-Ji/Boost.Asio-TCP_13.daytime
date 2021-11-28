#define _CRT_SECURE_NO_WARNINGS
#include <ctime>
#include <iostream>
#include<string>
#include<boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

string make_daytime_string() {
	time_t now = time(0);
	return ctime(&now);
}

int main()
{
	try {
		boost::asio::io_service io_service;
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));
		while (1)
		{
			tcp::socket socket(io_service);
			acceptor.accept(socket);
			string message = make_daytime_string();
			boost::system::error_code ignored_error;
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		}
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
	}
	return 0;
}