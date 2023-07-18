class Nav {

    constructor(options) {

        // a reference to the current object scope - used later with the click event listener
        let obj = this;
        // an options settings object - the default values are overridden with possible parameter settings of the same name
    	this.options = $.extend({
            theme     : 'sandbox',
    		name      : 'mainnav',
            clsss     : []

    	}, options);

    	// a reference to the current nav element
        this.element = options.element;
		// a reference to the current nav element as a jquery object
        this.$element = $(this.element);        
        // the div[data-mainnav] selector only selects the elements with a data-mainnav attribute
        this.$pages = $('div[data-'+this.options.name+']');

        // a reference to the current index - for hiding the previous page on click
        this.curIndex = 0;
        this.$curElement = null;

        // Initiate the navigation using the uikit navigation component
        UIkit.navbar(this.element, {});

        // Set an event listener on the a tags within the navigation
        $(this.element).find('a').on("click", function(evt){
            obj.changePage(evt);
            return false;

        });

    }

    changePage(evt) {
    	// the currentTarget is the a element - one up is the parent li element
        let $el = $(evt.currentTarget).parent('li'), route = $el.data('api') && $el.data('api').length? $el.data('api') : '';
        this.$curElement = $el;
        
        // check if we are in a dropdown link
        if( $el.parent('ul').hasClass('uk-navbar-dropdown-nav') )
            $el = $el.parent('ul').parent('div').parent('li');

        let $cur = $('div[data-'+this.options.name+'="index_' + this.curIndex + '"'), gotExtraClass = this.options.clsss[this.curIndex] || false;

        // hide the previously current page element
        $cur.addClass(this.options.theme+'-hide');

        // add special class if needed
        if( gotExtraClass && gotExtraClass.length )
            $cur.addClass(gotExtraClass);

        // set the curIndex - as a reference to hide a previous page on click later
        this.curIndex = $el.index();

        // show only the current page element
        $('div[data-'+this.options.name+'="index_' + this.curIndex + '"').removeClass(this.options.theme+'-hide');

        if( this.options.name === 'mainnav' ){
            $('html').css({'background-image': 'url(/img/index_'+this.curIndex+'.jpg)'});

        }

        // check for a callback
        let afterclick = this.options.callbacks.click || false;
        if( afterclick )
            afterclick( evt, this.curIndex, {route: route} );

        // log the current index
        console.log('current index for '+ this.options.name + ' = ' + $el.index());

    }

}