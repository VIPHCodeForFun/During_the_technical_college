class App {

    constructor(options) {
        let obj = this;
        this.window = options.root; // A reference to the window root object in which the variable app has been defined
        this.templates = options.templates || {};
        this.BH = null; // A reference to the Bloodhound Object - used like a flag to know if Bloodhound has already been initiated or not
        $.each(this.templates, function(key, valueObj) {
            Handlebars.registerPartial('app.templates.' + key, valueObj); // For using the partial within other partials

        });

    }

    run() {
        this.mainnav = new Nav({
            theme: 'hian',
            element: document.getElementById('hian_main_nav'),
            clsss: ['', '', 'hian-opa-0'],
            callbacks: {
                'click': function(evt, idx, param) {
                    idx = parseInt(idx, 10);
                    if (param && param.route && param.route.length) {
                        // call the api for the data
                        // assign handlers immediately after making the request
                        $.get('/api/' + param.route)
                            .done(function(data) {
                                var $container = $('div[data-mainnav="index_2"]');
                                $container.empty().html(app.templates.newsitems({ title: $(evt.currentTarget).text(), items: data })).removeClass('hian-opa-0');
                                // Just a Demo using the php crud api
                                // https://github.com/mevdschee/php-crud-api
                                // Set the listener on the image and title of the article
                                // The zoom icon is handled in the main.less - CSS
                                $container.find('div.newsitem-banner').on('click', app.newsItemOnClickHandler);
                                // Within this function - in the GET scope - we need to call the root "app" object
                                app.initTypeahead();

                            })
                            .fail(function(data) {
                                alert("error at api call\napp.run in AppClass.js @ mainnav");

                            })
                            .always(function(data) {
                                // Check for an error in the data - the data should be a json array with (or without) entries
                                if (!data || typeof data !== 'object')
                                    alert(data);

                            });

                    }

                }

            }

        });
        // preload background images
        const imgs = [];
        for (var i = 0; i < 9; i++) {
            imgs[i] = new Image();
            imgs[i].src = '/img/index_' + i + '.jpg';

        }

    }

    initTypeahead() {
        // init the bloody hound source
        if (this.BH)
            this.BH.clearPrefetchCache().clearRemoteCache(); // Finally - after 1.5 hours - this did the cache trick - the last call particularly - 06.01.2021

        this.BH = new Bloodhound({
            datumTokenizer: Bloodhound.tokenizers.obj.whitespace('value'),
            queryTokenizer: Bloodhound.tokenizers.whitespace,
            prefetch: '',
            remote: {
                url: '/api/search?str=%QUERY',
                wildcard: '%QUERY',
                filter: function(records) {
                    var divs;
                    // Remove the mark-tags by unwrapping the contents within
                    $('mark.search-result').contents().unwrap();
                    // Re-Render the newsitems
                    // Doing it the "pure JavaScript way" here - without jQuery - just as a demo
                    for (var i = 0; i < records.length; i++) {
                        records[i].innerRender = true;
                        divs = document.querySelectorAll('div.uk-card[data-id="' + records[i].id + '"]');
                        for (var r = 0; r < divs.length; r++) {
                            divs[r].innerHTML = app.templates.newsitem(records[i]);
                            // Need to reset the listener on the newsbanner
                            // After re-rendering the innerHTML the click handler for the banner is gone ...
                            divs[r].querySelector('div.newsitem-banner').addEventListener('click', app.newsItemOnClickHandler);
                            // Note that the event is always passed on as an argument - writing it like so would lead to the same thing:
                            /*
                            divs[r].querySelector('div.newsitem-banner').addEventListener('click', function(evt){
                                app.newsItemOnClickHandler(evt);
                                return false;

                            });*/

                        }

                    }
                    // The filter function is normally used to filter the suggestions coming from the fetch
                    // In our case we don't need to filter the data - so we just pass on the records as they are
                    // We used this function only to re-render the newsitems containing the search string           
                    return records;

                }
            }

        });
        // init the typeahead for the article
        this.$typeahead = $('body').find('input[name="search-input"]').typeahead({
            minLength: 3,
            highlight: true

        }, {
            display: 'label',
            limit: 10,
            source: this.BH

        }).on('typeahead:selected', function(e, record) {
            // console.log( record );
            // render the item by itself
            app.renderArticle(record);

            $(this).typeahead('val', record.search); // Remove the selected value in the search input
            $('form.search-form').find('input.uk-input').removeClass('loader-oval');

        }).on('typeahead:asyncrequest', function() {
            $('form.search-form').find('input.uk-input').addClass('loader-oval');

        }).on('typeahead:asynccancel typeahead:asyncreceive', function(e, q, r) {
            $('form.search-form').find('input.uk-input').removeClass('loader-oval');

        });

    }

    renderArticle(record) {
        record.single = true; // this will make the close button render - clicking close will re-render all items
        record.innerRender = false;
        $('div.news-items').empty().html(app.templates.newsitem(record));
        // Add a listener on the close button - call re-render on click
        $(document.getElementById('newsitem_close')).on('click', function() {
            // Re-render the lazy way - just trigger a click on the current nav element set in the NavClass
            if (app.mainnav.$curElement)
                app.mainnav.$curElement.find('a').eq(0).trigger('click');

        });


    }

    newsItemOnClickHandler(evt) {

        var $element = $(evt.currentTarget).closest('div.uk-card');
        $.get('/crud/api.php/records/article/' + $element.data('id'))
            .done(function(record) {
                app.renderArticle(record);

            })
            .fail(function(data) {
                alert("error at crud api call");

            })
            .always(function(data) {
                // Check for an error in the data - the data should be a json array with (or without) entries
                if (!data || typeof data !== 'object')
                    alert(data);

            });

        return false;// prevent bubling up

    }

}