#ifndef _MQTT_H
#define _MQTT_H

#include <MQTTAsync.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MQTTAsync.h>
#include <unistd.h>
#include <gpio.h>
#include <utilities.h>

#define ADDRESS "tcp://192.168.0.17:1883"
#define CLIENTID "ExampleClientSub"
#define TOPIC1 "lights/+"
#define TOPIC2 "camera"
#define TOPIC3 "doors"
#define QOS 1
#define TIMEOUT 10000L
#define USERNAME "embebidos1"
#define PASSWORD "EmbebidosProgra1"

void connlost(void *context, char *cause);
int msgarrvd(void *context, char *topicName, int topicLen, MQTTAsync_message *message);
void onDisconnect(void *context, MQTTAsync_successData *response);
void onSubscribe(void *context, MQTTAsync_successData *response);
void onSubscribeFailure(void *context, MQTTAsync_failureData *response);
void onConnectFailure(void *context, MQTTAsync_failureData *response);
void onConnect(void *context, MQTTAsync_successData *response);
void onSend(void *context, MQTTAsync_successData *response);
void sendMessage(char *payload, char *topic);
void initMqtt(int *pins, int size);

#endif
