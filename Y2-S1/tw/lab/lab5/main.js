var c = 0
function inc() {
    ++c
    document.getElementById('counter').innerHTML=c;
}

window.addEventListener("load", ()=> {
    var btn = document.createElement('Button')
    btn.innerHTML = 'Push me!'

    var d = document.getElementById('counter')

    btn.addEventListener('click', inc)
    var newNode = d.parentNode.insertBefore(btn, d)
})
