function processPage() {
	console.log("Event Listener Triggered");
	var divs = document.getElementsByTagName('div');
	for (var i = 0, l = divs.length; i < l; i++) {
		console.log("Length of Divs = " + divs.length);
		var id = divs[i].getAttribute("id");
		if(id != null){
			if(id.includes("feed_stream")){
				var children = divs[i].children;
				// divs[i] is now the <div> object holding all of the posts

				// Children now contains each object on the wall. children[0] = posting block, children[1:] = comments
				for(var j = 1, m = children.length; j < m; j++){
					postDict = {};
					console.log("Child" + j + ", a POST on the WALL...")


					var user_contents = children[j].getElementsByTagName('p');
					if(user_contents != null){
						for(var k = 0, n = user_contents.length; k < n; k++){
							var user_content_value = user_contents[k].innerText;
							var user_content_key = "USER:"+j;
							postDict[user_content_key] = user_content_value;
							//console.log("USER: " + user_content_value);
						}
					}

					var media_contents = children[j].getElementsByTagName('a');
					if(media_contents != null){
						for(var k = 0, n = media_contents.length; k < n; k++){
							if(media_contents[k].getAttribute("class") == "uiStreamSponsoredLink"){
								console.log("MEDIA: SPONSORED LINK");
								children[j].parentNode.removeChild(children[j]);
								m--;
								break;
							}
							var hrefStr = media_contents[k].getAttribute("href")						
							if(hrefStr != null){
								if(hrefStr.includes("https://www.facebook.com")){
									var media_content_key = "MEDIA:"+j;
							 		postDict[media_content_key] = hrefStr;
									//console.log("MEDIA: href = " + hrefStr);
								}
							}
						}
					}
					console.log("PRINTING DICT")
					for(var key in postDict){
						var value = postDict[key];
						console.log(value);
					}
				}
				break;
			}


			//If we removed a block, need to recalculate divs.length
			if( divs.length != l ){
				console.log("Removed a Section, need to recalculate")
				divs = document.getElementsByTagName('div');
				l = divs.length;
				i--;
			}
		}
		//images[i].src = 'https://placekitten.com/' + images[i].width + '/' + images[i].height;
	}

	//setTimeout(processPage, 5000);
}

document.addEventListener("DOMContentLoaded", processPage());
document.addEventListener("click",processPage());