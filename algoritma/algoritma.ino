void loop(){
  
  if(ada gak tanaman){
    if(Umur Tanaman < Umur Panen){
      ml = TakaranSiraman(Umur Tanaman)
      Siram(ml)
    }else{
       Panen
    } 
  }
  
  else{
    Tidak Siram();
  }
  
}
