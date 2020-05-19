	window.setInterval(
    () => {
        console.log("%d", Temperatuur);
        fetch("HTTP_Senver.c")
        .then((res) => res.text())
        .then((res) => {
            console.log(res);
            if(res=="checked") {
                document.getElementById("temperature").innerHTML = Temperatuur; 
            }
            else {
                document.getElementById("checkboxButton").removeAttribute('checked');
            }           
        });
    },
    3000
);
