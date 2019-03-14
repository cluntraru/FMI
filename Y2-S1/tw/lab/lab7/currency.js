window.addEventListener('load', ()=> {
    let app = new Vue({
        el: '#table',
        data: {
            curr: [{
                Data: 'orice',
                EUR: 5,
                USD: 4
            }]
        },

        created: ()=>{
            let x = new XMLHttpRequest();
            x.onreadystatechange = function() {
                if (this.readyState === 4 && this.status === 200) {
                    let data = x.responseText;
                    console.log(data);
                }
            }

            x.open('GET', 'https://play.trixbits.ro/data/currency.csv');
            x.send();
        }
    })

});