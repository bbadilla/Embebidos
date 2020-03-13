const express = require("express"),
  passport = require("passport"),
  bodyParse = require("body-parser"),
  localStrategy = require("passport-local"),
  passportLocalMongoose = require("passport-local-mongoose"),
  mongoose = require("mongoose");

const User = require("./models/user");

const PORT = process.env.PORT || 5000;

const mongoURI = "mongodb://sebasrs:Embebidos123@ds141671.mlab.com:41671/cangrejito";
mongoose.connect(mongoURI, { useUnifiedTopology: true, useNewUrlParser: true });

const app = express();
app.set("view engine", "ejs");

app.use(require("express-session")({
  secret: "embedded systems are fun I love them",
  resave: false,
  saveUninitialized: false
}));
app.use(passport.initialize());
app.use(passport.session());

passport.serializeUser(User.serializeUser());
passport.deserializeUser(User.deserializeUser());

app.get("/", (req, res) => {
  res.render("smartView");
});

require("./routes/authRoutes");

app.listen(PORT, () => {
  console.log(`Listening on port: ${PORT}`);
});