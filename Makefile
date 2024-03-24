all:
#	g++ tcp-Server.cpp -o server
#	g++ tcp-Client.cpp -o client
	g++ -pthread testcpp0001.cpp -o testcpp 
	./testcpp