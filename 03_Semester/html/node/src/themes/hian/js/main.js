/*
    templates is the variable holding the handlebars compiled templates from the theme templates directory
    in the gruntfile the namespace is set to "templates" - making it accessable here for passing on into the app class object
    in the gruntfile the uglify settings are such, that the templates are included in the main.js before the AppClass is declared and run here in the main.js
*/
this.app = new App({
    root            : this,
    templates       : templates

});
this.app.run();
console.log('App initiated and run from the main.js file');
