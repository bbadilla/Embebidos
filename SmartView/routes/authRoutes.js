module.exports = (app, User, passport, isLoggedIn) => {
  // Login routes
  app.get("/login", (req, res) => {
    res.render("login");
  });

  app.post("/login", passport.authenticate("local", {
    successRedirect: "/",
    failureRedirect: "/login"
  }), (req, res) => {
  });

  // Registration routes
  app.post("/register", (req, res) => {
    let username = req.body.username;
    let password = req.body.password;
    User.register(new User({ username: username }), password, (err, user) => {
      if (err) {
        console.log(err);
        res.redirect('/login');
      }
      passport.authenticate("local")(req, res, () => {
        res.redirect("/");
      });
    });
  });

  // Logout  route
  app.get("/logout", (req, res) => {
    req.logout();
    res.redirect("/login");
  });
}