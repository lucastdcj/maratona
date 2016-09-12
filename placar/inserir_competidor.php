<html>
  <head>
    <title>Placar - Inserir competidor</title>
  </head>
  <body>

  <font face="Verdana">

  <h1>Inserir competidor</h1>

  <form action="" name="form" method="post">
  id<br />
  <input type="text" name="id" style="width:300px;" />
  <br /><br /> 
  seu nome<br />
  <input type="text" name="nome" style="width:300px;" />
  <br /><br />
  <input type="submit" value="Enviar" name="acao" />
  </form>
<?php
  $id = $_POST['id'];
  $nome = $_POST['nome'];

  if($_POST['acao'] == "Enviar") {
    if(empty($id) || empty($nome)) {
      echo "<h1>Complete o formul&aacute;rio. Competidor n&atilde;o inserido.</h1>";
    } else {
      $arquivo = fopen("participantes.conf", "a");
      fwrite($arquivo, "$id $nome\n");
      fclose($arquivo);

      echo "<h1>Competidor inserido corretamente!</h1>";
    }
  }
?>
  </font>
Instru&ccedil;&otilde;es para inserir seu login:<BR><BR>
 
<b>ATEN&Ccedil;&Atilde;O VOCE DEVE USAR O MESMO NOME (n&atilde;o o mesmo ID) PARA TODOS OS JU&Iacute;ZES</b><BR><BR>

  <b>uva.onlinejudge.org / livearchive.onlinejudge.org</b><BR>
    Submeta qualquer codigo para qualquer problema, em seguida v&aacute; em Site Statistics -> Last 50 Submissions, coloque o mouse sobre seu nome e utilize o <i>userid</i> que consta no link<BR><BR>

    <b>Spoj</b><BR>
    ID = Seu login<BR><BR>

  <b>Timus</b><BR>
    ID = Seu c&oacute;digo de submiss&atilde;o sem as 2 letras finais verificadoras<BR><BR>
    
  <b>URI</b><BR>
    Fa&ccedil;a login e coloque o mouse sobre o link Profile/Perfil no topo. Use o n&uacute;mero no final do link.<BR><BR>
  </body>

</html>
