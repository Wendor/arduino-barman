const path = require('path');
const fs = require('fs');
const png = require("png-js");
const glob = require("glob");

glob("./images/**/*.png", function (er, files) {
  for(let file of files) {
    const bitmap = png.load(file);

    png.decode(file, function(pixels) {
      pixels = [...pixels];
    
      pixels = arrayChunk(pixels, 4).map(pixel => pixel[0] && pixel[1] && pixel[2] ? '1' : '0');
      let picture = arrayChunk(pixels, bitmap.width).map(line => line);
    
      let tempResult = [];
      for(let x = 0; x < picture.length; x++) {
        for(let y = 0; y < picture[x].length; y++) {
          if(!tempResult[y]) tempResult[y] = [];
          tempResult[y][x] = picture[x][y];
        }
      }
      tempResult = tempResult.map(line => line.reverse());

      //console.log(tempResult.map(line => line.join(',')));
    
      let result = [];
      let parts = bitmap.height / 8;
    
      for(let i = parts -1; i >= 0; i--) {
        tempResult.forEach(line => result.push(line.slice(8*i, 8*i + 8)));
      }
    
      const classname = path.basename(file).split('.').slice(0, -1).join('.');
      const dir = path.dirname(file);
      arrayToCpp(classname, result, dir);
    });
  }
})

function arrayChunk(array, chunk=8) {
  let i,j,result = [];
  for (i=0, j=array.length; i<j; i+=chunk) {
    result.push(array.slice(i,i+chunk));
  }
  return result;
}

function arrayToCpp(name, array, dir) {
  let result = array.map(line => '0b' + line.join('')).join(",\n  ");
  let content = `
static const uint8_t ${name}[] PROGMEM = {
  ${result}
};`.trim();
  const filename = dir+"/"+name+".cpp";
  console.log(filename);
  console.log(content+"\n");
  fs.writeFileSync(filename, content);
}