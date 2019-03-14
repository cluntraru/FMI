window.addEventListener('load', ()=>{
    let divs = document.getElementsByClassName('targetclass')

    for (var i in divs) {
        if (divs[i].tagName !== 'DIV') {
            continue
        }

        let btn = document.createElement('button')
        btn.innerHTML = 'Click me!'
        btn.addEventListener('click', function() {
            if (btn.innerHTML === 'Click me!') {
                btn.innerHTML = 'Clicked!'
            }
            else {
                btn.innerHTML = 'Click me!'
            }
        })

        divs[i].parentNode.insertBefore(btn, divs[i])
    }
})
