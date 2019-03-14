function init() {
    var table = new Vue({
        el: '#table',
        data: {
            col: [
            {
                NUME: 'Ion',
                SERIE: 'AB',
                NUMAR: 845622
            },
            {
                NUME: 'Andreea',
                SERIE: 'DA',
                NUMAR: 849822
            }
            ]
        }
    })

    var table2 = new Vue({
        el: '#table2',
        data: {
            col: [
            {
                NUME: 'Ion',
                SERIE: 'AB',
                NUMAR: 845622
            },
            {
                NUME: 'Andreea',
                SERIE: 'DA',
                NUMAR: 849822
            }
            ]
        }
    })
}

window.addEventListener('load', init);