1 start server
	* function
		you can start the server by server.bat in the root path
	* parameters (server.bat in line "start QtPredict.exe [IP | IP port]")
		* IP : you can specify your owner ip address which will be changed in some time;
				defalut 0.0.0.0
		* port : you also can specify it, defalut 8888
				when the port value is conflict with other server or this server has already started,
				you should change the value of it or close the server which using the port

2 function
	* first step,  this server is used to generator the key sequence of every game
	* second step, this server can calculate the rules for package which is the most important for your demand
		* Note : when you want to calculate, you should have two files which is generator.bin(first step to get it) 
		  and key.bin(maybe it is the name of 'config' in U3D)
	* final step, this server can check the correction of rules calculated in second step
		* Note : this step can judge whether the rule is good for game or not simply. 
		  If the result is not acceptable, you can use more generation samples to calculate until you get a good order
		  Then, you can use mobile to check it through different speeds of network

3 question
	* if you have some problem using it, welcome to ask for help
	* there are some suggestions when you started the server
		  
Enjoy it