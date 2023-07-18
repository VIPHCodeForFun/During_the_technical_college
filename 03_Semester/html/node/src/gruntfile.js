/*
  Written by Ray van den Berge - ray@cp.run - ComfortPages.com
*/
module.exports = function(grunt) {

    'use strict';

    grunt.initConfig({
        // pkg: grunt.file.readJSON('package.json'),
        // config.json structured object - you can change the theme here for your final future zone work
        siteconfig: grunt.file.readJSON('config.json').site,
        theme: '<%= siteconfig.theme %>',
        cssframework: '<%= siteconfig.cssframework %>',
        // Directory variables
        lessDirFrameWork: "less/<%= siteconfig.cssframework %>/less/",
        jsDirTheme: "themes/<%= siteconfig.theme %>/js/",
        tplDirTheme: "themes/<%= siteconfig.theme %>/templates/",
        distillDir: "../web/",
        cssDir: "css/",
        jsDir: "js/",
        // Copy task - for moving files fom src to web
        copy: {
            html: {
                // Simple replace for the html to load the right js and css - dev / prod
                options: {
                    process: function(content, srcpath) {

                        var theme = grunt.config.get('theme'),
                            cnt = content.replace(/_cssframework_/gi, grunt.config.get('cssframework'));
                        cnt = cnt.replace(/_theme_/gi, theme);

                        // Log in gitbash in yellow - theme name and mode- dev or production
                        console.log('\x1b[33m%s\x1b[0m', 'Running theme ' + theme + ' - mode ' + ((grunt.option('prod')) ? 'prod' : 'dev'));
                        if (grunt.option('prod')) {
                            return cnt.replace(/_ver_/gi, ".min");

                        } else {
                            return cnt.replace(/_ver_/gi, "");

                        }

                    }

                },
                files: [{
                    expand: true,
                    cwd: 'themes/<%= siteconfig.theme %>/html/',
                    src: ['*.html'],
                    dest: '<%=distillDir %>'

                }]
            },
            imgs: {
                // Copy the images
                files: [{
                    expand: true,
                    cwd: 'themes/<%= siteconfig.theme %>/img/',
                    src: ['*.jpg', '*.gif', '*.png', '*.svg'],
                    dest: '<%=distillDir %>img/'
                }]

            },
            // For the favicon and later robots.txt etc.
            rootfiles: {
                files: [{
                    expand: true,
                    cwd: 'themes/<%= siteconfig.theme %>/',
                    src: ['*.ico'],
                    dest: '<%=distillDir %>'

                }]

            }

        },
        // Run LESS CSS compilation
        less: {
            compile: {
                files: {
                    '<%= distillDir %><%= cssDir %><%= siteconfig.cssframework %>.css': '<%= lessDirFrameWork %><%= siteconfig.cssframework %>.less',
                    '<%= distillDir %><%= cssDir %><%= siteconfig.theme %>.css': 'themes/<%= siteconfig.theme %>/less/*.less'
                }
            }
        },
        // Runs CSS tasks
        postcss: {
            dev: {
                options: {
                    map: false,
                    processors: [
                        require('pixrem')(), // add fallbacks for rem units
                        require('autoprefixer')() // add vendor prefixes
                    ]

                },
                files: {
                    '<%= distillDir %><%= cssDir %><%= siteconfig.theme %>.css': '<%= distillDir %><%= cssDir %><%= siteconfig.theme %>.css'

                }

            },
            prod: {
                options: {
                    map: false,
                    processors: [
                        require('pixrem')(), // add fallbacks for rem units
                        require('autoprefixer')(), // add vendor prefixes
                        require('cssnano')() // minify the result
                    ]
                },
                files: {
                    '<%= distillDir %><%= cssDir %><%= siteconfig.cssframework %>.min.css': '<%= distillDir %><%= cssDir %><%= siteconfig.cssframework %>.css',
                    '<%= distillDir %><%= cssDir %><%= siteconfig.theme %>.min.css': '<%= distillDir %><%= cssDir %><%= siteconfig.theme %>.css'
                }

            }

        },
        // Run js tasks
        /* 
          The ! in the '<%= jsDirTheme %>*.js', '!<%= jsDirTheme %>main.js', '<%= jsDirTheme %>main.js'
          is there to make sure the main.js gets inlcluded last - making sure the components and templates are loaded first

        */
        uglify: {
            dev: {
                options: {
                    compress: false,
                    beautify: true,
                    preserveComments: true

                },
                files: {
                    '<%= distillDir %><%= jsDir %>main.js': ['<%= jsDirTheme %>*.js', '!<%= jsDirTheme %>templates.js', '!<%= jsDirTheme %>main.js', '<%= jsDirTheme %>templates.js', '<%= jsDirTheme %>main.js', 'js/dev.js']

                }

            },
            prod: {
                options: {
                    compress: true,
                    preserveComments: false

                },
                files: {
                    '<%= distillDir %><%= jsDir %>main.min.js': ['<%= jsDirTheme %>*.js', '!<%= jsDirTheme %>templates.js', '!<%= jsDirTheme %>main.js', '<%= jsDirTheme %>templates.js', '<%= jsDirTheme %>main.js']

                }

            }

        },
        // Watch tasks for developement mode - automatically start tasks if theme files are changed
        watch: {
            options: {
                // The uglify task injects a dev.js file from src/js with a tiny WebSocket script for the live reload to work
                // Listening on the default port 80 doesn't work because of restricted node access
                // This way it's a clean solution - the script is automatically left out @ production
                livereload: {
                    host: 'localhost',
                    port: 35729

                }

            },
            js: {
                files: ['themes/<%= siteconfig.theme %>/js/*.js', '!<%= jsDirTheme %>templates.js', 'themes/<%= siteconfig.theme %>/templates/*.hbs', 'js/dev.js'],
                tasks: ['clean:js', 'handlebars:compile', 'uglify:dev']
            },
            css: {
                files: ['themes/<%= siteconfig.theme %>/less/*.less', 'less/<%= siteconfig.cssframework %>/less/*.less'],
                tasks: ['clean:dev', 'less', 'postcss:dev']
            },
            html: {
                files: ['themes/<%= siteconfig.theme %>/html/*.html'],
                tasks: ['copy']

            },
            images: {
                files: ['themes/<%= siteconfig.theme %>/img/*'],
                tasks: ['copy:imgs']

            }            

        },
        handlebars: {
            compile: {
                options: {
                    namespace: 'templates',
                    processName: function(filePath) {
                        var pieces = filePath.split("/");
                        return pieces[pieces.length - 1].replace('.hbs', '');

                    }

                },
                files: {
                    '<%= jsDirTheme %>templates.js': ['<%= tplDirTheme %>*.hbs']

                }

            }

        },
        // Clean folders/files for production - so you can upload (onto a live server) the whole web folder when done
        clean: {
            options: {
                force: true // dangerous but needed to get out of this directory - upwards ...

            },
            dev: [
                '<%= distillDir %><%= cssDir %><%= siteconfig.theme %>.min.css',
                '<%= distillDir %><%= cssDir %><%= siteconfig.cssframework %>.min.css',
                '<%= distillDir %><%= jsDir %>main.min.js'
            ],
            js: [
                '<%= distillDir %><%= jsDir %>main.min.js',
                '<%= distillDir %><%= jsDir %>main.js'
            ],
            prod: [
                '<%= distillDir %><%= cssDir %><%= siteconfig.theme %>.css',
                '<%= distillDir %><%= cssDir %><%= siteconfig.cssframework %>.css',
                '<%= distillDir %><%= jsDir %>main.js'

            ],
            img: ['<%= distillDir %>img/**']

        }

    });
    // make sure you have a package.json file in this root directory
    // Grunt plugins
    // npm install handlebars --save-dev
    // npm install grunt-contrib-handlebars --save-dev
    grunt.loadNpmTasks('grunt-contrib-handlebars');

    // npm install grunt-contrib-clean --save-dev
    grunt.loadNpmTasks('grunt-contrib-clean');
    // npm install grunt-postcss pixrem autoprefixer cssnano --save-dev
    // make sure to install 9.8.6 - postcss doesn't support the latest version !!!
    // npm install autoprefixer@9.8.6 --save-dev
    // npm install pixrem --save-dev
    // npm install grunt-cssnano --save-dev
    // npm install grunt-postcss --save-dev
    grunt.loadNpmTasks('grunt-postcss');

    // npm install grunt-contrib-less --save-dev
    grunt.loadNpmTasks('grunt-contrib-less');


    // Fix for es6: https://davidburgos.blog/how-to-fix-grunt-contrib-uglify-for-es6/
    // npm install gruntjs/grunt-contrib-uglify#harmony --save-dev
    grunt.loadNpmTasks('grunt-contrib-uglify-es');

    // npm install grunt-contrib-copy --save-dev
    grunt.loadNpmTasks('grunt-contrib-copy');

    // npm install grunt-contrib-watch --save-dev
    grunt.loadNpmTasks('grunt-contrib-watch');

    // differ if production or developement version
    var taskArray = [];
    if (grunt.option('prod')) {
        taskArray = ['clean:img', 'copy', 'less', 'postcss:prod', 'handlebars:compile', 'uglify:prod', 'clean:prod'];

    } else {
        taskArray = ['clean:dev', 'copy', 'less', 'postcss:dev', 'handlebars:compile', 'uglify:dev', 'watch'];

    }
    grunt.registerTask('default', taskArray);

};