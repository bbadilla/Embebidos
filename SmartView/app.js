const express = require("express");

const app = express();
app.set("view engine", "ejs");

const PORT = process.env.PORT || 5000;

app.get("/", (req, res) => {
  res.render("smartView");
});

app.listen(PORT, () => {
  console.log(`Listening on port: ${PORT}`);
});