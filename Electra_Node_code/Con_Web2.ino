String Con_Web2(int id, int UlStat){
  HTTPClient http; //--> Declare object of class HTTPClient

  delay(100);

  //----------------------------------------Getting Data from MySQL Database
  String GetAddress, LinkGet, getData;
  
  GetAddress = "ArduiT2/SetData.php"; 
  LinkGet = host + GetAddress; //--> Make a Specify request destination

  getData = "ID=" + String(id) + "&Stat=" + String(UlStat);
  Serial.println("----------------Connect to Server-----------------");
  Serial.println("Set Motion Status to Database");
  Serial.print("Request Link : ");
  Serial.println(LinkGet);
  http.begin(LinkGet); //--> Specify request destination
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
  int httpCodeGet = http.POST(getData); //--> Send the request
  //String payloadGet = http.getString(); //--> Get the response payload from server
  Serial.print("Response Code : "); //--> If Response Code = 200 means Successful connection, if -1 means connection failed. 
  Serial.println(httpCodeGet); //--> Print HTTP return code
  //Serial.print("Returned data from Server : ");
  //Serial.println(payloadGet); //--> Print request response payload
  
  //return (payloadGet);
  
  Serial.println("----------------Closing Connection----------------");
  http.end(); //--> Close connection
  Serial.println();
  Serial.println("Please wait 1 seconds for the next connection.");
  Serial.println();
}
