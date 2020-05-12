module.exports = app => {
  app.post('/sendMessage', (req, res) => {
    // Todo el codigo para mandar algo por MQTT
    let message = req.body.message;
    res.send(`OK me llego ${message}`);
  })
}