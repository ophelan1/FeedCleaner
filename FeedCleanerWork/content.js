function processPage() {
	console.log("Event Listener Triggered");
	var divs = document.getElementsByTagName('div');
	for (var i = 0, l = divs.length; i < l; i++) {


		var id = divs[i].getAttribute("id");
		if(id != null){

			//if id.includes("feed_stream") then divs[i] is the object with all the posts in it 
			if(id.includes("hyperfeed") && id.length > 20 ){
				console.log("substream");
				var post = divs[i];
				console.log(post);
				var postDict = {};

				// children[j] is the post in question, user_contents is the paragraphs of user text within the post block
				var user_contents = post.getElementsByTagName('p');
				if(user_contents != null){
					for(var k = 0, n = user_contents.length; k < n; k++){
						var user_content_value = user_contents[k].innerText;
						var user_content_key = "USER:"+k;
						postDict[user_content_key] = user_content_value;
					}
				}


				//media_contents is the links and other media references within the text block
				var media_contents = post.getElementsByTagName('a');
				if(media_contents != null){
					for(var k = 0, n = media_contents.length; k < n; k++){
						if(media_contents[k].getAttribute("class") == "uiStreamSponsoredLink"){
							postDict["SPONSOR:"+k] = "media_sponsored";
						}
						var hrefStr = media_contents[k].getAttribute("href")						
						if(hrefStr != null){
							if(hrefStr.includes("https://www.facebook.com")){
								var media_content_key = "MEDIA:"+k;
						 		postDict[media_content_key] = hrefStr;
								//console.log("MEDIA: href = " + hrefStr);
							}
						}
					}
				}
				console.log("PRINTING DICT");
				for(var key in postDict){
					var value = postDict[key];
					if(value != null){
						if(searchSet.has(value)){
							console.log("Key: " + key + ", Value:" + value);
							console.log("Contains BAD String, removing....")


							post.parentNode.removeChild(post);
							j = 0;
							break;
						}
						else{
							console.log(value);
						}
					}
				}
				
			}


			//If we removed a block, need to recalculate divs.length
			if( divs.length != l ){
				console.log("Removed a Section, need to recalculate")
				divs = document.getElementsByTagName('div');
				l = divs.length;
				i = 0;
			}
		}
		//images[i].src = 'https://placekitten.com/' + images[i].width + '/' + images[i].height;
	}
}

searchSet = new Set(["media_sponsored","buzzfeed","theodysseyonline","distractify","elitedaily","unilad","washingtonpost","philadelphiaunion","theladbible"])
processPage();