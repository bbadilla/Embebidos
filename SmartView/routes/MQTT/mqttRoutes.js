const mqtt = require('mqtt');

//Var of lisghts and doors
c1= 0;c2= 0;c3= 0;c4= 0; c5 = 0; c6 =0;
door1=0; door1Aux=0;
door2=0; door2Aux=0;
door3=0; door3Aux=0;
door4=0; door4Aux=0;

module.exports = app => {

  var options = {
    port: 11079 ,
    host: 'mqtt://soldier.cloudmqtt.com',
    username: 'user1',
    password: '0000',
  };

  var mqttMessage;

  let client = mqtt.connect('mqtt://soldier.cloudmqtt.com', options);
  client.on("connect",function(){ 
    client.subscribe('doors/+');
    console.log("connected");
  });

  client.on('message', (topic, message) => {
    if(message=='1'){
      switch (topic) {
        case 'doors/6':
          door1++;
          return handleConnected(message)
        case 'doors/13':
          door2++;
          return handleConnected(message)
        case 'doors/19':
          door3++;
          return handleConnected(message)
        case 'doors/26':
          door4++;
          return handleConnected(message)
      }
    }else{
      console.log('No handler for topic %s', topic)
    }
  })

  function handleConnected (message) {
    mqttMessage = message.toString();
    console.log('Message from MQTT: %s', message)
  }

  app.get('/getMessageDoor1', function(req, res) {
    if(door1!=door1Aux){
      if (mqttMessage) {
        res.send(mqttMessage);
        door1Aux++;
      } 
    }else {
        res.status(404).send();
    }
  });

  app.get('/getMessageDoor2', function(req, res) {
    if(door2!=door2Aux){
      if (mqttMessage) {
        res.send(mqttMessage);
        door2Aux++;
      } 
    }else {
        res.status(404).send();
    }
  });

  app.get('/getMessageDoor3', function(req, res) {
    if(door3!=door3Aux){
      if (mqttMessage) {
        res.send(mqttMessage);
        door3Aux++;
      } 
    }else {
        res.status(404).send();
    }
  });

  app.get('/getMessageDoor4', function(req, res) {
    if(door4!=door4Aux){
      if (mqttMessage) {
        res.send(mqttMessage);
        door4Aux++;
      } 
    }else {
        res.status(404).send();
    }
  });


  //Send messages to turn on or off lights
  app.post('/sendMessage', (req, res) => {
    // Var Message
    let message = req.body.message;
    //View msg in website
    res.send(`OK me llego ${message}`);
    
    //Logic for lights
    //A little logic .... :)
    if (message=='btn1'){
      if(c1%2==0){
        client.publish("lights/17", '1;')
        c1=1;
      }else{
        client.publish("lights/17", '0;')
        c1=0;
      }
    }
    if (message=='btn2'){
      if(c2%2==0){
        client.publish("lights/27", '1;')
        c2=1;
      }else{
        client.publish("lights/27", '0;')
        c2=0;
      }
    }
    if (message=='btn3'){
      if(c3%2==0){
        client.publish("lights/22", '1;')
        c3=1;
      }else{
        client.publish("lights/22", '0;')
        c3=0;
      }
    }
    if (message=='btn4'){
      if(c4%2==0){
        client.publish("lights/10", '1;')
        c4=1;
      }else{
        client.publish("lights/10", '0;')
        c4=0;
      }
    }
    if (message=='btn5'){
      if(c5%2==0){
        client.publish("lights/9", '1;')
        c5=1;
      }else{
        client.publish("lights/9", '0;')
        c5=0;
      }
    }
    if(message=='mainbtn') {
      if(c1%2!=0 && c2%2!=0 && c3%2!=0 && c4%2!=0 &&c5%2!=0 ){
        c6 = 1;
      }
      if(c6%2==0){
          client.publish("lights/1", 'allOn;')
          c6=1;
          c1=c2=c3=c4=c5=1;

      }else{
        if(c1%2==0 ||c2%2==0 || c3%2==0 || c4%2==0 ||c5%2==0 ){
          client.publish("lights/1", 'allOn;')
          c6=1;
          c1=c2=c3=c4=c5=1;
        }else{
          client.publish("lights/1", 'allOff;')
          c6=0;
          c1=c2=c3=c4=c5=0;
        }
      }
    }
  })
}