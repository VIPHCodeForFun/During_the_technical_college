                    <?php
                    $navitem = array(
                      'one' => "Netzpolitik",
                      'two' => "B2B",
                      'one' => "Produkte",


                    );
                    $html = "<ul>";
                      foreach ($navitem as $key => $value) {
                        $html .= "<li><a href='/'' class='netz'>".$value."</a></li>";

                      }
                    echo "</ul>". $html;
                    ?>