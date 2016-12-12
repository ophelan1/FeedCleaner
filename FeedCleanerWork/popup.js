function hello() {
	console.log("RUNNING HELLO");
  chrome.tabs.executeScript({
    file: "/content.js"
  }); 
}

document.getElementById('clickme').addEventListener('click', hello)