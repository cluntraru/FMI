let funcCode = 0;

window.addEventListener('load', function() {
    // Change function that is called on click
    setTimeout(function() {
        funcCode = 1;
    }, 10000);

    // let theDiv = document.getElementById('the-div');
    let theDiv = document.querySelector('#the-div');
    theDiv.addEventListener('click', function(ev) {
        // ev.stopPropagation();
        // ev.preventDefault();
        // ev.stopImmediatePropagation();
        if (funcCode == 0) {
            alert('Elementele sunt inactive');
        }
        else {
            alert('Ati dat click in afara elementelor');
        }
    });

    for (child of theDiv.children) {
        child.addEventListener('click', function(ev) {
            ev.stopPropagation();
            console.log(this.style.visibility);
            if (funcCode == 1 && this.style.visibility == 'hidden') {
                this.style.visibility = 'visible';
            }
            else if (funcCode == 1) {
                this.style.visibility = 'hidden';
            }
        })
    }
});
