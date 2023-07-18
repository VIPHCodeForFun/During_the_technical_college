<?php
/**
 * App - A tiny PHP API "Framework" - as a demo for working with MySQL - PDO - PHP
 * Writter during the Winter Semester 2021 - 2022 for the Fachhochschule Salzburg
 * 
 * @author Ray van den Berge ray@cp.run - ComfortPages.com
 */
class App
{
  
  private $config;
  private $db;
  public $dataroutes;
  private $search_result_length = 40;
  /**
  * Class constructor
  * @param object - passed from the index.php - a small config object with mostly the database settings
  * @return nothing
  */
  function __construct( $config ){
    $this->config = $config;
    $this->dataroutes = array('current','main','mostread','newest');
    /*
        Only establish a database connection in case we are NOT using the json files
          -> the static version as opposed to the database dynamic version as defined at the app initiation in the index.html
    */
    if( !isset($_GET['api']) || $_GET['api'] === 'dynamic' )
      $this->db = new DbConnect( $config->db );

  }
  /**
  * The heart of the "Framework"
  * This function is always called and defines which route to take 
  *
  * @param none - it uses the server request URL to define which route it responds to
  * @return array - echo in JSON Format - or a SVG image in one special case - as a DEMO
  */
  public function run(){

    $return = array(); // define $return up front - return empty array if no results
    $path = $_SERVER['REQUEST_URI']; // for example /api/newest or /api/search?str=######&api=static
    $route = basename($path, ".php"); // $route is set to for example "newest" or search?str=######&api=static

    if( strpos( $route, "?") !== FALSE )
      $route = substr( $route, 0, strrpos( $route, '?') );// Gets rid of the parameters - like for the search search?str=####### -> this becomes "search"

    if( in_array( $route, $this->dataroutes ) ){
      // Example
      // route /api/newest

      // We are in our Mini API for serving the json data
      // Query the db
      $stmt = $this->db->conn->prepare("SELECT DISTINCT article.*, category.label as catlabel, category.color FROM article
                                          JOIN section ON section.id = article.section_id
                                            JOIN category ON category.id = article.category_id
                                              WHERE section.route=:route");

      // Bind Parameter - secure passing of parameters - preventing MySQL injections
      $stmt->bindParam(':route', $route, PDO::PARAM_STR);
      $stmt->execute();
      
      if ( $stmt->errorCode() == 0 ) {
        $return = $stmt->fetchAll();

        array_walk( $return, function( &$item, $key ){

          array_walk( $item, function(&$i, $k){
            $i = !empty($i) && is_string($i) && preg_match( "/id$/", $k)? (int)$i : $i;

          });
          $item = (object)$item;
          // $item->color = str_replace( "#", "", $item->color);

          unset($item->label);

        });

      }

    }elseif ( $route === 'search' ) {
      // Example
      // route /api/search?str=Teslas
      $return = $this->applySearch();

    }elseif( $route === 'svg' ){
      // Example
      // /api/svg?img=search&color=cccccc
      $color = !isset($_GET['color']) || empty($_GET['color'])? '#333333' : '#'.str_replace( "#", "", $_GET['color'] );// Defaults to dark gray with 333333
      $img = !isset($_GET['img'])? '' : $_GET['img'];// Defaults in the switch to a checkmark

      switch ( $img ) {
        case 'search':
          $svg = '<?xml version="1.0" encoding="utf-8"?><!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd"><svg version="1.1" xmlns="http://www.w3.org/2000/svg" width="512" height="512" viewBox="0 0 512 512"><g id="icomoon-ignore"></g><path fill="'.$color.'" d="M496.131 435.698l-121.276-103.147c-12.537-11.283-25.945-16.463-36.776-15.963 28.628-33.534 45.921-77.039 45.921-124.588 0-106.039-85.961-192-192-192s-192 85.961-192 192 85.961 192 192 192c47.549 0 91.054-17.293 124.588-45.922-0.5 10.831 4.68 24.239 15.963 36.776l103.147 121.276c17.661 19.623 46.511 21.277 64.11 3.678s15.946-46.449-3.677-64.11zM192 320c-70.692 0-128-57.308-128-128s57.308-128 128-128 128 57.308 128 128-57.307 128-128 128z"></path></svg>';
          break;
        
        default:
          // checkmark - just for fun
          $svg = '<?xml version="1.0" encoding="utf-8"?><!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN" "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd"><svg version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink" width="512" height="512" viewBox="0 0 512 512"><path fill="'.$color.'" d="M491.529 32c-167.25 126.583-327.651 295.9-327.651 295.9l-115.59-103.9-48.288 49.189c47.508 44.651 157.581 162.599 194.816 206.811 104.795-175.090 213.739-305.668 317.184-425.077l-20.471-22.923z" ></path></svg>';

          break;

      }
      header('Content-type:image/svg+xml');
      echo $svg;

      exit();

    }else{
      $return = array("message" => "no route for $path" );

    }
    // Set the header response for json
    header('Content-type:application/json;charset=utf-8');

    // Respond the result as a json encoded string
    echo json_encode( $return );

  }
  /**
  * applies the search on the database or static json files with the GET parameter
  * Some entries seem to be duplicated - for example - run this query in phpmyadmin - there are 3 entries
  * SELECT * FROM `article` WHERE `header` like '%Google steckt%'
  *
  * @param string GET str search
  * @return array - gets echo-ed by the main run function
  */
  protected function applySearch(){

    $return = array();
    // $_POST, $_GET are the PHP global arrays with the passed parameters of the request
    if( empty($_GET['str']) || strlen($_GET['str']) < 2 )
      return $return;

    $searchString = $_GET['str'];
    $search = "/$searchString/i";
    $toSearch = array('header','text');
    $replacement = '<mark class="search-result">$0</mark>';    

    // The database - dynamic - search
    $stmt = $this->db->conn->prepare("SELECT DISTINCT article.*, article.text as label, category.color, category.label as catlabel
                                          FROM article
                                            JOIN category ON category.id = article.category_id
                                              WHERE CONCAT(article.header,' ', article.text, ' ', article.image) LIKE :search ORDER BY header");

    $searchString = "%".$_GET['str']."%";

    $stmt->bindParam(':search', $searchString, PDO::PARAM_STR );
    $stmt->execute();

    if( $stmt->errorCode() == 0 ){
      
      $return = $stmt->fetchAll();
      // Here i got stuck for a bit on 15.01.2021 - cause I forgot to pass the parameters $search and $replacement with "use"
      // Without the "use" they are not available within the scope of the array_map function
      $return = array_map( function( $arr ) use ($search, $replacement) {    
        // The label is an extra property to use in the typeahead suggestion
        // The label should not have HTML tags - cause it is rendered automatically with the tt-highlight span tag by typeahead
        $arr['label'] = empty($arr['header'])? strip_tags($arr['text']) : strip_tags($arr['header']);       
        /* 
            ********************************** To Do **********************************

            Here you could go crazy !!!
            For example : add the color of the category to the mark tag with an inline style attribute
            Be creative :-)

        */
        $arr['text'] = preg_replace( $search, $replacement, $arr['text'] );
        $arr['catlabel'] = preg_replace( $search, $replacement, $arr['catlabel'] );       
        $arr['header'] = preg_replace( $search, $replacement, $arr['header'] );
        $arr['color'] = $arr['color'];
        $arr['hideWrap'] = true;
        $arr['search'] = $_GET['str'];

        return $arr;

      }, $return );

    }

    return $return;

  }

  protected function getCategoryByLabel( $label ){
    
    $return = NULL;

    // Query the db
    $stmt = $this->db->conn->prepare("SELECT DISTINCT * FROM category WHERE label=:label");
    $stmt->bindParam(':label', $label, PDO::PARAM_STR); // Bind Parameter - securer passing of parameters - preventing MySQL injections
    $stmt->execute();
    
    if ( $stmt->errorCode() == 0 )
      $return = $stmt->fetch();

    return $return;

  }

  protected function getSectionByRoute( $route ){
    
    $return = NULL;

    // Query the db
    $stmt = $this->db->conn->prepare("SELECT DISTINCT * FROM section WHERE route=:route");

    $stmt->bindParam(':route', $route, PDO::PARAM_STR); // Bind Parameter - securer passing of parameters - preventing MySQL injections
    $stmt->execute();
    
    if ( $stmt->errorCode() == 0 )
      $return = $stmt->fetch();

    return $return;

  }

  protected function insertArticle( $data ){

    $return = FALSE;

    $stmt = $this->db->conn->prepare("INSERT INTO `article` (`id`, `category_id`, `section_id`, `creationtime`, `header`, `text`, `image`, `url`) VALUES (NULL, :category_id, :section_id, CURRENT_TIMESTAMP, :header, :txt, :src, :url);");

    $stmt->bindParam(':category_id', $data->category_id, PDO::PARAM_INT);
    $stmt->bindParam(':section_id', $data->section_id, PDO::PARAM_INT);

    $header = !empty($data->header)? $data->header : '';
    $stmt->bindParam(':header', $header, PDO::PARAM_STR);

    $txt = !empty($data->text) ? $data->text : '';
    $stmt->bindParam(':txt', $txt, PDO::PARAM_STR);

    $src = !empty($data->image) ? $data->image : '';
    $stmt->bindParam(':src', $src, PDO::PARAM_STR);

    $url = !empty($data->url) ? $data->url : '#';
    $stmt->bindParam(':url', $url, PDO::PARAM_STR);    
    
    try {
      $stmt->execute();
      $return = TRUE;

    } catch (Exception $e) {
      $return = FALSE;
      
    }
    return $return;

  }

  protected function createTables(){
    // Create Category Table
    $stmt = $this->db->conn->prepare("CREATE TABLE `category` (
        `id` int(11) NOT NULL,
        `label` varchar(255) NOT NULL DEFAULT '',
        `title` varchar(255) NOT NULL DEFAULT '',
        `color` varchar(100) NOT NULL
      ) ENGINE=InnoDB DEFAULT CHARSET=utf8;");   

    $stmt->execute();

    // Fill Category Table
    $stmt = $this->db->conn->prepare("INSERT INTO `category` (`id`, `label`, `title`, `color`) VALUES
        (1, 'b2b', 'Business to Business', '#82b478'),
        (2, 'netzpolitik', 'Netzpolitik', '#5aa490'),
        (3, 'digital-life', 'Digital Life', '#c83c82'),
        (4, 'games', 'Games', '#e75d01'),
        (5, 'produkte', 'Produkte', '#145ad2'),
        (6, 'science', 'Science', '#ffb432');");

    $stmt->execute();

    // Add primary key id
    $stmt = $this->db->conn->prepare("ALTER TABLE `category` ADD PRIMARY KEY (`id`)");
    $stmt->execute();
    // Add auto increment
    $stmt = $this->db->conn->prepare("ALTER TABLE `category` CHANGE `id` `id` INT(11) NOT NULL AUTO_INCREMENT;");
    $stmt->execute();    


    // Create Section Table
    $stmt = $this->db->conn->prepare("CREATE TABLE `section` (
          `id` int(11) NOT NULL,
          `route` varchar(255) NOT NULL DEFAULT '',
          `label` varchar(100) NOT NULL DEFAULT ''
        ) ENGINE=InnoDB DEFAULT CHARSET=utf8");   

    $stmt->execute();

    // Fill Section Table
    $stmt = $this->db->conn->prepare("INSERT INTO `section` (`id`, `route`, `label`) VALUES
        (1, 'newest', 'Newest'),
        (2, 'current', 'Current'),
        (3, 'main', 'Main'),
        (4, 'mostread', 'Most Read')");

    $stmt->execute();

    // Add section key id
    $stmt = $this->db->conn->prepare("ALTER TABLE `section` ADD PRIMARY KEY (`id`)");
    $stmt->execute();
    // Add auto increment
    $stmt = $this->db->conn->prepare("ALTER TABLE `section` CHANGE `id` `id` INT(11) NOT NULL AUTO_INCREMENT;");
    $stmt->execute();        


    // Create Article Table
    $stmt = $this->db->conn->prepare("CREATE TABLE `article` (
        `id` int(11) NOT NULL,
        `category_id` int(11) NOT NULL DEFAULT '0',
        `section_id` int(11) NOT NULL DEFAULT '0',
        `creationtime` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP,
        `header` varchar(255) NOT NULL DEFAULT '',
        `text` text NOT NULL,
        `image` varchar(255) NOT NULL DEFAULT '',
        `url` varchar(255) NOT NULL DEFAULT ''
      ) ENGINE=InnoDB DEFAULT CHARSET=utf8");   

    $stmt->execute();

    // Add article key id
    $stmt = $this->db->conn->prepare("ALTER TABLE `article` ADD PRIMARY KEY (`id`)");
    $stmt->execute();
    // Add auto increment
    $stmt = $this->db->conn->prepare("ALTER TABLE `article` CHANGE `id` `id` INT(11) NOT NULL AUTO_INCREMENT;");
    $stmt->execute();

    // Add indexes to speed up the join statement for getting the articles
    $stmt = $this->db->conn->prepare("ALTER TABLE `article` ADD INDEX `cat_sec_index` (`category_id`,`section_id`)");
    $stmt->execute();

  }

}
