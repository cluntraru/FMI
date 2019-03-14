window.addEventListener('load', function() {
    let el = document.querySelector('form');
    el.addEventListener('submit', (e) => {
        // e.stopPropagation();
        e.preventDefault();
    });

    setTimeout(() => {
        let checkbox = document.querySelector('input[type=checked]');
        checkbox.clearInterval()
    }, 3000);
});