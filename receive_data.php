<?php
date_default_timezone_set('Asia/Jakarta');
// Konfigurasi database MySQL
$servername = "servername";
$username = "username";
$password = "password";
$dbname = "dbname";

// Ambil data dari POST request
$sensor = $_POST['sensor'];
$lokasi = $_POST['lokasi'];
$data1 = $_POST['data1'];
$data2 = $_POST['data2'];
$data3 = $_POST['data3'];
$keterangan = $_POST['keterangan'];
$waktu =date("Y-m-d H:i:s");

// Buat koneksi ke database
$conn = new mysqli($servername, $username, $password, $dbname);

// Periksa koneksi
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

// Siapkan SQL untuk menyimpan data
$sql = "INSERT INTO sensor_data (sensor, lokasi,data1, data2,data3, keterangan,waktu) VALUES ('$sensor', '$lokasi', '$data1', '$data2', '$data3', '$keterangan', '$waktu')";

// Eksekusi SQL dan periksa hasilnya
if ($conn->query($sql) === TRUE) {
  echo "Data inserted successfully";
} else {
  echo "Error: " . $sql . "<br>" . $conn->error;
}

// Tutup koneksi
$conn->close();
?>
