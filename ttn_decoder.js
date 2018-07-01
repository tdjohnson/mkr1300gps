function Decoder(bytes, port) {
  var decoded = {};

 
    var payload = String.fromCharCode.apply(null, bytes);
    decoded.latitude = parseFloat(payload.substr(0,9));
    decoded.longitude= parseFloat(payload.substr(9,9));
    decoded.altitude = parseFloat(payload.substr(18,6));
    decoded.hdop = parseFloat(payload.substr(24,5));

    
  return decoded;
}
