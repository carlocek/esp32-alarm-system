String request;

String GetValue(String myLM, String LMst, String myWL, String COPst,String  DRst, String myTP, String bg_L, String bg_W, String bg_T, String contL, String contW,String contT, String myUM)
{
request = R"====(

<!DOCTYPE html>
<html lang="en">

<head>
<title>test pagina progetto laboratorio</title>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>

* {
  box-sizing: border-box;
}

.row {  
  display: -ms-flexbox; /* IE10 */
  display: flex;
  -ms-flex-wrap: wrap; /* IE10 */
  flex-wrap: wrap;
}

.footer{
        background-color: #333;
        padding:10px;
        width: 100%;
        height: 80px;
        bottom: 0;
      }

.side {
  -ms-flex: 30%; /* IE10 */
  flex: 30%;
  padding: 20px;
  border-style:double;
  border-width:9px;
  border-right-color:#333;
  border-left-style:none;
  border-top-style:none;
  border-bottom-style:none;
  
}

.fakeimg {
  width: 60%;
  height:10%
  padding: 30px;
  margin:20px;
  margin-left:60px;
}

.main {   
  -ms-flex: 70%; /* IE10 */
  flex: 70%;
  padding: 20px;
}

.impianto{
  background-color:white;
  float:left;white;
  width:75%;
  padding:20px;
  border-style:double;
  border-color:grey;
  border-width:5px;
  border-right-style:none;
  height:160px;
  margin-left:20px
 }  


.stato{
  background-color:white;
  float:left;
  width:20%;
  padding:20px;
  height:160px;
 }
 
body{
 margin: 0;
} 

.navbar {
  overflow: hidden;
  background-color: #333;
  position: sticky;
  position: -webkit-sticky;
  top: 0;
  margin-bottom:0;
}

/* Style the navigation bar links */
.navbar a {
  float: left;
  display: block;
  color: white;
  text-align: center;
  padding: 14px 20px;
  text-decoration: none;
  margin-bottom:0;
}

.navbar a.active {
  background-color: #666;
  color: white;
}

.navbar a:hover {
  background-color: #ddd;
  color: black;
}

.div1{
 background-color:#2F4F4F;
 padding-top:15px;
 height:100px;
 }
 
</style>
</head>

<body>



<div class="div1" style="padding-top:5px;">

<h1 style="text-align:center;color:white;font-family: Merriweather, serif;">SISTEMA DI CONTROLLO AUTOMATIZZATO</h1>

</div>


<div class="navbar">
  <a href="/" class="active">Home</a>
  <a href="https://firebase.google.com/?hl=it&safe=active">Database</a>
</div>

<div style="background-image:URL('https://besthqwallpapers.com/img/original/75086/gray-metal-pattern-4k-metal-texture-dark-metal-gray-metal-background.jpg');
 background-size:cover;"> 

<div class="row">
<div class="side">
<div style="border-style:double;border-color:grey;margin:25px;margin-top:30px;background-color:#333;padding:5px">

<p style="padding-left:10px;color:white;">Il progetto simula un sistema di controllo automatizzato per gli impianti di copertura, illuminazione e drenaggio di uno stadio. <br>In questa pagina è possibile visualizzare lo stato di ciascuno degli impianti con annesso valore del parametro di riferimento. <br>
   Ciascun attuatore si attiva al superamento di una soglia percentuale stabilita. I parametri riportati fanno riferimento ai dati in tempo reale, in parallelo a questi, i valori restituiti dai sensori sono inviati su base periodica ad un database su firebase al quale è possibile accedere dall'apposito link. 
   <br>Sono inoltre indicati per ciascun impianto i sensori utilizzati con relativo link al datasheet.</p>

</div>

<div class="fakeimg">
<img src="https://images.vexels.com/media/users/3/136913/isolated/preview/8eeb83410d11efae50bda7dd229c92f4-stadium-icon-by-vexels.png" style="width:100%;height:100&;">
</div>

</div>
<br>

<div class="main">
<section style="background-color:#333;border-style:double;border-color:grey;margin-left:50px;margin-right:50px;margin-bottom:20px;margin-top:30px">

<div style="overflow:auto">
   
   <div class="impianto" style="margin-top:30px">
   <p><b style="font-size:20px;">IMPIANTO DI ILLUMINAZIONE</b></p>
   <p><b>LUMINOSITA': )====" + myLM + R"====(</b></p>
   <p><b><a href="http://www.klsele.com/admin/product_upload/20190322144057KLS6-3537..pdf">Fotoresistore</a> utilizzato per la rilevazione del livello di luminosità</b></p>
   </div>
   
   <div class="stato" style="margin-top:30px; background-color:)====" + bg_L + R"====(;border-style:double;border-width:5px;border-color:)====" + contL + R"====(">
   <p style="text-align:center;font-size:20px"><b>STATO</b></p>
   <p style="text-align:center"><b>)====" + LMst + R"====(</b></p>
   </div>
   
</div>

<br><br>

<div style="overflow:auto">
   
   <div class="impianto">
   <p><b style="font-size:20px;">IMPIANTO DI DRENAGGIO</b></p>
   <p><b>LIVELLO DELL'ACQUA: )====" + myWL + R"====(</b></p>
   <p><b><a href="https://curtocircuito.com.br/datasheet/sensor/nivel_de_agua_analogico.pdf">Sensore</a> utilizzato per la rilevazione del livello dell'acqua</b></p>
   </div>
   
   <div class="stato" style="background-color:)====" + bg_W + R"====(;border-style:double;border-width:5px;border-color:)====" + contW + R"====(">
   <p style="text-align:center;font-size:20px"><b>STATO</b></p>
   <p style="text-align:center"><b>)====" + DRst + R"====(</b></p>
   </div>
   
</div>

<br><br>

<div style="overflow:auto">
   
   <div class="impianto" style="margin-bottom:30px">
   <p><b style="font-size:20px;">IMPIANTO DI COPERTURA</b></p>
   <p><b>TEMPERATURA: )====" + myTP + R"====(      UMIDITÀ: )====" + myUM + R"====(</b></p>
   <p><b><a href="https://www.mouser.com/datasheet/2/758/DHT11-Technical-Data-Sheet-Translated-Version-1143054.pdf">Sensore</a> utilizzato per la rilevazione di temperatura e umidità</b></p>
   </div>
   
   <div class="stato" style="margin-bottom:30px; background-color:)====" + bg_T + R"====(;border-style:double;border-width:5px;border-color:)====" + contT + R"====(">
   <p style="text-align:center;font-size:20px"><b>STATO</b></p>
   <p style="text-align:center"><b>)====" + COPst + R"====(</b></p>
   </div>
   
</div>
</section>
</div>
</div>
</div>
 <footer>
            <h5 style="text-align:center; color:white">Copyright &copy;&reg; 2021, Leonardo Di Iorio & Carlo Ceccherelli</h5>
 </footer>
</body>
</html>)====";

return request;
}
