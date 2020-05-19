#include <mqtt.h>

MQTTAsync client;
volatile MQTTAsync_token deliveredtoken;
MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
MQTTAsync_message pubmsg = MQTTAsync_message_initializer;

int disc_finished = 0;
int subscribed = 0;
int finished = 0;

int PIN_SIZE = 0;
int *ledPins = NULL;

void connlost(void *context, char *cause)
{
  MQTTAsync client = (MQTTAsync)context;
  MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
  int rc;

  printf("\nConnection lost\n");

  printf("Reconnecting\n");
  conn_opts.keepAliveInterval = 20;
  conn_opts.cleansession = 1;
  if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
  {
    printf("Failed to start connect, return code %d\n", rc);
    finished = 1;
  }
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTAsync_message *message)
{
  char *payloadptr;
  char **arrTopic = NULL;
  char **arrPayload = NULL;

  payloadptr = message->payload;

  for (int i = 0; i < message->payloadlen; i++)
  {
    putchar(*payloadptr++);
  }

  putchar('\n');

  split(topicName, '/', &arrTopic);
  split(message->payload, ';', &arrPayload);

  if (!strcmp(arrTopic[0], "lights"))
  {
    if (!strcmp(arrPayload[0], "allOn"))
    {
      setPinsValue(ledPins, PIN_SIZE, 1);
    }
    else if (!strcmp(arrPayload[0], "allOff"))
    {
      setPinsValue(ledPins, PIN_SIZE, 0);
    }
    else
    {
      printf("Pin #%d set to %d\n", atoi(arrTopic[1]), atoi(arrPayload[0]));
      digitalWrite(atoi(arrTopic[1]), atoi(arrPayload[0]));
    }
  }

  MQTTAsync_freeMessage(&message);
  MQTTAsync_free(topicName);

  free(arrTopic);
  free(arrPayload);

  return 1;
}

void onDisconnect(void *context, MQTTAsync_successData *response)
{
  printf("Successful disconnection\n");
  disc_finished = 1;
}

void onSubscribe(void *context, MQTTAsync_successData *response)
{
  printf("Subscribe succeeded\n");
  subscribed = 1;
}

void onSubscribeFailure(void *context, MQTTAsync_failureData *response)
{
  printf("Subscribe failed, rc %d\n", response ? response->code : 0);
  finished = 1;
}

void onConnectFailure(void *context, MQTTAsync_failureData *response)
{
  printf("Connect failed, rc %d\n", response ? response->code : 0);
  finished = 1;
}

void onConnect(void *context, MQTTAsync_successData *response)
{
  MQTTAsync client = (MQTTAsync)context;
  MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
  int rc;

  printf("Successful connection\n");

  opts.onSuccess = onSubscribe;
  opts.onFailure = onSubscribeFailure;
  opts.context = client;

  deliveredtoken = 0;

  if ((rc = MQTTAsync_subscribe(client, TOPIC1, QOS, &opts)) != MQTTASYNC_SUCCESS)
  {
    printf("Failed to start subscribe to topic 1, return code %d\n", rc);
    exit(EXIT_FAILURE);
  }

  if ((rc = MQTTAsync_subscribe(client, TOPIC2, QOS, &opts)) != MQTTASYNC_SUCCESS)
  {
    printf("Failed to start subscribe to topic 2, return code %d\n", rc);
    exit(EXIT_FAILURE);
  }
}

void onSend(void *context, MQTTAsync_successData *response)
{
  MQTTAsync client = (MQTTAsync)context;
  MQTTAsync_disconnectOptions opts = MQTTAsync_disconnectOptions_initializer;
  int rc;

  printf("Message with token value %d delivery confirmed\n", response->token);

  opts.context = client;

  if ((rc = MQTTAsync_disconnect(client, &opts)) != MQTTASYNC_SUCCESS)
  {
    printf("Failed to start sendMessage, return code %d\n", rc);
    exit(EXIT_FAILURE);
  }
}

void sendMessage(char *payload, char *topic)
{
  int rc;

  opts.context = client;

  pubmsg.payload = payload;
  pubmsg.payloadlen = (int)strlen(payload);
  pubmsg.qos = QOS;
  pubmsg.retained = 0;
  deliveredtoken = 0;

  if ((rc = MQTTAsync_sendMessage(client, topic, &pubmsg, &opts)) != MQTTASYNC_SUCCESS)
  {
    printf("Failed to start sendMessage, return code %d\n", rc);
    exit(EXIT_FAILURE);
  }
}

void initMqtt(int *pins, int size)
{
  PIN_SIZE = size;
  ledPins = malloc(size * sizeof(int));
  memcpy(ledPins, pins, size * sizeof(int));

  MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
  MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;
  int rc;

  MQTTAsync_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);

  MQTTAsync_setCallbacks(client, client, connlost, msgarrvd, NULL);

  conn_opts.username = USERNAME;
  conn_opts.password = PASSWORD;
  conn_opts.keepAliveInterval = 20;
  conn_opts.cleansession = 1;
  conn_opts.onSuccess = onConnect;
  conn_opts.onFailure = onConnectFailure;
  conn_opts.context = client;
  if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
  {
    printf("Failed to start connect, return code %d\n", rc);
    exit(EXIT_FAILURE);
  }

  while (!subscribed)
    usleep(10000L);
}