<?php
    $id= $_POST['id']
    $name= $_POST['name']
    $Dest= $_POST['Dest']
    $budget= $_POST['budget']
    $conn= new my sqli('localhost','root','test');
    if($conn->connect_error){
        die('Connection Failed : '.$conn->connect_error);
    }else{
        $stmt= $conn->prepare("insert into registration(id,name,Dest,budget)values(?,?,?,?)");
        $stmt->bind_param("issd",$id,$name,$Dest,$budget);
        $stmt->execute();
        $stmt->close();
        $conn->close();
    }
?>
