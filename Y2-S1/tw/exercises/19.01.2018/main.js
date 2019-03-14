let letter;

function addToList() {
    let theList = document.getElementById('the-list');
    if (!theList) {
        theList = document.createElement('ul');
        theList.id = "the-list";
        document.body.appendChild(theList);
    }

    let item = document.createElement('li');
    let background = document.getElementById('col-sel').value;
    item.style.background = background;

    let stringLen = document.getElementById('range').value;
    let string = '';
    for (let i = 0; i < stringLen; ++i) {
        string += letter;
    }

    item.innerHTML = string;

    let oldHTML = string;
    let timer;
    item.addEventListener('mouseenter', function() {
        if (timer) {
            clearTimeout(timer);
        }

        this.innerHTML = 'salut!';
    });

    item.addEventListener('mouseout', function() {
        let that = this;
        timer = setTimeout(function() {
            console.log(oldHTML);
            that.innerHTML = oldHTML;
        }, 2000);
    });

    theList.appendChild(item);
}

window.addEventListener('load', function() {
    letter = prompt();
    while (letter.length != 1 || ((letter < 'a' || letter > 'z') && (letter < 'A' || letter > 'Z'))) {
        letter = prompt();
    }
});