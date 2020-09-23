Action()
{
	lr_start_transaction("UC_3_Buy_Ticket_And_View_Itinerary");

	lr_start_transaction("open_web_tours");

	web_set_sockets_option("SSL_VERSION", "2&3");

	web_add_auto_header("Sec-Fetch-Site", 
		"none");

	web_add_auto_header("Sec-Fetch-Dest", 
		"document");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

    web_reg_save_param("userSession",
		"LB=userSession\" value=\"",
		"RB=\"",
		LAST);
		
	web_reg_find("Fail=NotFound",
		"Text=A Session ID has been created and loaded into a cookie called MSO.",
		LAST);

	web_url("WebTours", 
		"URL=http://localhost:1080/WebTours/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
		
	lr_end_transaction("open_web_tours",LR_AUTO);
	
	lr_start_transaction("login");

	web_revert_auto_header("Sec-Fetch-User");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	lr_think_time(5);
	
	web_reg_find("Fail=NotFound",
		"Text=User password was correct",
		LAST);

	web_submit_data("login.pl",
		"Action=http://localhost:1080/cgi-bin/login.pl",
		"Method=POST",
		"TargetFrame=body",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
		"Snapshot=t2.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={Login}", ENDITEM,
		"Name=password", "Value={Password}", ENDITEM,
		"Name=login.x", "Value=74", ENDITEM,
		"Name=login.y", "Value=13", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);
	
	lr_end_transaction("login",LR_AUTO);

	lr_start_transaction("find_flights");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");
	
	web_reg_find("Fail=NotFound",
		"Text= User has returned to the search page",
		LAST);

	web_url("Search Flights Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("find_flights",LR_AUTO);

	lr_start_transaction("fill_fields_about_flight");

	web_add_auto_header("Origin", 
		"http://localhost:1080");

	lr_think_time(5);
	
	web_reg_find("Fail=NotFound",
		"Text=Flight departing from <B>{CityDepart}</B> to <B>{CityArrive}</B> on <B>{DepartDate}</B>",
		LAST);
	
	/*Correlation comment - Do not change!  Original value='010;386;09/15/2020' Name ='outboundFlight' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=outboundFlight",
		"TagName=input",
		"Extract=value",
		"Name=outboundFlight",
		"Ordinal={random_id}",
		"Type=radio",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		LAST);
	
	web_reg_save_param("flight_id",
		"LB=name=\"outboundFlight\" value=\"",
		"RB=;",
		"Ord={random_id}",
		LAST);
		
	web_reg_save_param("flight_time",
		"LB=<td align=\"center\">",
		"RB=m<td align=\"center\">",
		"Ord={random_id}",
		LAST);
	

	web_submit_data("reservations.pl", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={CityDepart}", ENDITEM, 
		"Name=departDate", "Value={DepartDate}", ENDITEM, 
		"Name=arrive", "Value={CityArrive}", ENDITEM, 
		"Name=returnDate", "Value={ReturnDate}", ENDITEM, 
		"Name=numPassengers", "Value={numPassengers}", ENDITEM, 
		"Name=seatPref", "Value={SeatPref}", ENDITEM, 
		"Name=seatType", "Value={SeatType}", ENDITEM, 
		"Name=findFlights.x", "Value=47", ENDITEM, 
		"Name=findFlights.y", "Value=4", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		LAST);
	
	lr_end_transaction("fill_fields_about_flight",LR_AUTO);

	lr_think_time(5);

	lr_start_transaction("select_flight");
	
	web_reg_find("Fail=NotFound",
		"Text=Flight Reservation",
		LAST);

	web_submit_data("reservations.pl_2", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
		"Name=numPassengers", "Value={numPassengers}", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=seatType", "Value={SeatType}", ENDITEM, 
		"Name=seatPref", "Value={SeatPref}", ENDITEM, 
		"Name=reserveFlights.x", "Value=36", ENDITEM, 
		"Name=reserveFlights.y", "Value=10", ENDITEM, 
		LAST);
	
	lr_end_transaction("select_flight",LR_AUTO);
	
	lr_start_transaction("fill_payment_details");

	web_revert_auto_header("Origin");

	web_revert_auto_header("Sec-Fetch-User");

	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_header("Origin", 
		"http://localhost:1080");

	lr_think_time(5);
	
	web_reg_find("Fail=NotFound",
		"Text=Thank you for booking through Web Tours",
		LAST);

	web_reg_find("Fail=NotFound",
		"Text={DepartDate} :  {flight_time}m : Flight {flight_id} leaves {CityDepart}  for {CityArrive}.<br>",
		LAST);

	if (atoi(lr_eval_string("{numPassengers}")) == 1) {
	
	web_submit_data("reservations.pl_3", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value={FirstName}", ENDITEM,
		"Name=lastName", "Value={LastName}", ENDITEM,
		"Name=address1", "Value={City}", ENDITEM,
		"Name=address2", "Value={Street}", ENDITEM,
		"Name=pass1", "Value={FirstName} {LastName}", ENDITEM,
		"Name=creditCard", "Value={CreditCard}", ENDITEM,
		"Name=expDate", "Value={ExpDate}", ENDITEM,
		"Name=oldCCOption", "Value=", ENDITEM,
		"Name=numPassengers", "Value={numPassengers}", ENDITEM,
		"Name=seatType", "Value={SeatType}", ENDITEM,
		"Name=seatPref", "Value={SeatPref}", ENDITEM,
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=returnFlight", "Value=", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		"Name=buyFlights.x", "Value=32", ENDITEM, 
		"Name=buyFlights.y", "Value=8", ENDITEM, 
		"Name=.cgifields", "Value=saveCC", ENDITEM, 
		LAST);
		
	} else if (atoi(lr_eval_string("{numPassengers}")) == 2) {
		web_submit_data("reservations.pl_3",
        "Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value={FirstName}", ENDITEM,
		"Name=lastName", "Value={LastName}", ENDITEM,
		"Name=address1", "Value={City}", ENDITEM,
		"Name=address2", "Value={Street}", ENDITEM,
		"Name=pass1", "Value={FirstName} {LastName}", ENDITEM,
		"Name=pass2", "Value={ExtraPass}", ENDITEM,
		"Name=creditCard", "Value={CreditCard}", ENDITEM,
		"Name=expDate", "Value={ExpDate}", ENDITEM,
		"Name=oldCCOption", "Value=", ENDITEM,
		"Name=numPassengers", "Value={numPassengers}", ENDITEM,
		"Name=seatType", "Value={SeatType}", ENDITEM,
		"Name=seatPref", "Value={SeatPref}", ENDITEM,
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=returnFlight", "Value=", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		"Name=buyFlights.x", "Value=15", ENDITEM,
		"Name=buyFlights.y", "Value=10", ENDITEM,
		"Name=.cgifields", "Value=saveCC", ENDITEM,
		LAST);

	} else if (atoi(lr_eval_string("{numPassengers}")) == 3) {
		web_submit_data("reservations.pl_3",
        "Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=firstName", "Value={FirstName}", ENDITEM,
		"Name=lastName", "Value={LastName}", ENDITEM,
		"Name=address1", "Value={City}", ENDITEM,
		"Name=address2", "Value={Street}", ENDITEM,
		"Name=pass1", "Value={FirstName} {LastName}", ENDITEM,
		"Name=pass2", "Value={ExtraPass}", ENDITEM,
		"Name=pass3", "Value={ExtraPass}", ENDITEM,
		"Name=creditCard", "Value={CreditCard}", ENDITEM,
		"Name=expDate", "Value={ExpDate}", ENDITEM,
		"Name=oldCCOption", "Value=", ENDITEM,
		"Name=numPassengers", "Value={numPassengers}", ENDITEM,
		"Name=seatType", "Value={SeatType}", ENDITEM,
		"Name=seatPref", "Value={SeatPref}", ENDITEM,
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=returnFlight", "Value=", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		"Name=buyFlights.x", "Value=15", ENDITEM,
		"Name=buyFlights.y", "Value=10", ENDITEM,
		"Name=.cgifields", "Value=saveCC", ENDITEM,
		LAST);
	}

	
	lr_end_transaction("fill_payment_details",LR_AUTO);
	
	lr_start_transaction("open_itinerary");

    web_reg_find("Fail=NotFound",
		"Text=<b>Itinerary</font></b>",
		LAST);
	
	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(5);
	
	web_reg_find("Fail=NotFound",
		"Text=Flight Transaction Summary",
		LAST);


	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t19.inf", 
		"Mode=HTML", 
		LAST);
	
	
	
	web_revert_auto_header("Sec-Fetch-User");

	lr_end_transaction("open_itinerary",LR_AUTO);

	lr_start_transaction("logout");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(5);
	
	
	
	web_reg_find("Fail=NotFound",
		"Text= Also, the server options have been loaded into the cookie called",
		LAST);

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("logout",LR_AUTO);

	lr_end_transaction("UC_3_Buy_Ticket_And_View_Itinerary",LR_AUTO);

	return 0;
}