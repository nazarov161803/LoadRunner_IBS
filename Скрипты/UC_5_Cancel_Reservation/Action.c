Action()
{
	int flights_after_cancel = 0; 
	
	lr_start_transaction("UC_5_Cancel_Reservation");

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
		"Name=username", "Value={login}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM,
		"Name=login.x", "Value=60", ENDITEM,
		"Name=login.y", "Value=10", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);

	lr_end_transaction("login",LR_AUTO);

	lr_start_transaction("open_itinerary");
	
	
	web_reg_find("Fail=NotFound",
		"Text=Flight Transaction Summary",
		LAST);
	
	
	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(5);


	web_reg_save_param("flights_before_cancel",
		"LB=checkbox\" name=\"",
		"RB=\" value=",
		"Ord=ALL",
		LAST);

	
	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_end_transaction("open_itinerary",LR_AUTO);

	lr_start_transaction("cancel_flight");
		
	web_add_header("Origin", 
		"http://localhost:1080");
	

	lr_think_time(5);
	
	lr_save_string(lr_paramarr_random("flights_before_cancel"),"random_flight");  

	if (atoi(lr_eval_string("{Random}")) == 1) { //если будет выбран отмерна 1 билета, то он отменит один рандомный	

	web_submit_form("itinerary.pl",
	    ITEMDATA,
	    "Name={random_flight}", "Value=on", ENDITEM, 
	    "Name=removeFlights.x", "Value=53", ENDITEM, 
		"Name=removeFlights.y", "Value=4", ENDITEM,
		EXTRARES,
		"URL=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Referer=http://localhost:1080/cgi-bin/itinerary.pl", ENDITEM,
		LAST);
		
	} else if (atoi(lr_eval_string("{Random}")) == 2) {
		web_submit_form("itinerary.pl",
	    ITEMDATA,
	    "Name=1", "Value=on", ENDITEM,
		"Name=2", "Value=on", ENDITEM, 	    
	    "Name=removeFlights.x", "Value=53", ENDITEM, 
		"Name=removeFlights.y", "Value=4", ENDITEM,
		EXTRARES,
		"URL=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Referer=http://localhost:1080/cgi-bin/itinerary.pl", ENDITEM,
		LAST);
		
	} else if (atoi(lr_eval_string("{Random}")) == 3) {
		web_submit_form("itinerary.pl",
	    ITEMDATA,
	    "Name=1", "Value=on", ENDITEM,
		"Name=2", "Value=on", ENDITEM,
		"Name=3", "Value=on", ENDITEM,
	    "Name=removeFlights.x", "Value=53", ENDITEM, 
		"Name=removeFlights.y", "Value=4", ENDITEM,
		EXTRARES,
		"URL=http://localhost:1080/cgi-bin/itinerary.pl", 
		"Referer=http://localhost:1080/cgi-bin/itinerary.pl", ENDITEM,
		LAST);
	}
	
	web_reg_save_param("total",
		"LB=A total of ",
		"RB= scheduled flights",
		"Ord=1",
		LAST);
	
	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(5);

	
	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);
	
	
	
	flights_after_cancel = atoi(lr_eval_string("{total}"));

	
	if(atoi(lr_eval_string("{flights_before_cancel_count}")) <= flights_after_cancel) {
		lr_error_message("itinerary not deleted");
	} else if (atoi(lr_eval_string("{flights_before_cancel_count}")) > flights_after_cancel) {
		lr_output_message("itinerary success deleted");
	}

	
	
	lr_end_transaction("cancel_flight",LR_AUTO);
		                   
	lr_start_transaction("logout");
	

	web_revert_auto_header("Sec-Fetch-User");

	web_add_header("Sec-Fetch-User", 
		"?1");

	lr_think_time(5);
	
	
	web_reg_find("Fail=NotFound",
		"Text=A Session ID has been created and loaded into a cookie called MSO.",
		LAST);


	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("logout",LR_AUTO);

	lr_end_transaction("UC_5_Cancel_Reservation",LR_AUTO);

 	return 0;
}
