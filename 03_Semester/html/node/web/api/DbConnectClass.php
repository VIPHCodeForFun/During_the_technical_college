<?php
/**
 * Handling database connection
 
 */
class DbConnect {

    public $conn = NULL;
    /**
     * Establishing database connection
     * @return database connection handler
     */
    function __construct($config) {
        $opt = array(
            PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,
            PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
            PDO::ATTR_STRINGIFY_FETCHES  => FALSE,
            PDO::ATTR_EMULATE_PREPARES   => FALSE,
            PDO::MYSQL_ATTR_INIT_COMMAND => 'SET NAMES utf8'
            
        );

        try{
            $port = isset($config->port)? $config->port : 3306;
            // Connect to mysql database
            $this->conn = new PDO("mysql:host=".$config->host.";port=".$port.";dbname=".$config->name.";charset=utf8", $config->username, $config->password, $opt );            

        }catch(PDOException $error){
            die('connection error: '.$error->getMessage());

        }

    }

    /**
     * Check if a table exists in the current database.
     *
     * @param string $table Table to search for.
     * @return bool TRUE if table exists, FALSE if no table found.
     */
    public function tableExists($table) {
        // Try a select statement against the table
        // Run it in try/catch in case PDO is in ERRMODE_EXCEPTION.
        try {
            $result = $this->conn->query("SELECT 1 FROM $table LIMIT 1");

        } catch (Exception $e) {
            // We got an exception == table not found
            return FALSE;
        }
        // Result is either boolean FALSE (no table found) or PDOStatement Object (table found)
        return $result !== FALSE;

    }    

}
