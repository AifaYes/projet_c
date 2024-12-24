<?php
    $id= $_POST['id'];
    $name= $_POST['name'];
    $Dest= $_POST['Dest'];
    $budget= $_POST['budget'];
    $file="data.txt";
    $handle = fopen($file, 'w'); 

    if ($handle) {
        $data = "$id\n$name\n$Dest\n$budget\n";
        fwrite($handle, $data);
        fclose($handle);
        echo "success";
    }
?>
