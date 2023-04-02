document.addEventListener('DOMContentLoaded', function() {
    let correct_button = document.querySelector('.correct');
    let incorrect_buttons = document.querySelectorAll('.incorrect');


    correct_button.addEventListener('click', function() {
        correct_button.style.backgroundColor = 'green';
        document.querySelector('#feedback1').innerHTML = 'Correct!';
    });

    for (let i = 0; i < incorrect_buttons.length; i++) {
        incorrect_buttons[i].addEventListener('click', function() {
            incorrect_buttons[i].style.backgroundColor = 'red';
            document.querySelector('#feedback1').innerHTML = 'Incorrect!';
        });
    }

    let text_button = document.querySelector('.text_button');
    text_button.addEventListener('click', function() {
        let text_box = document.querySelector('.text_box');

        if (text_box.value.toLowerCase() == 'redbull') {
            document.querySelector('#feedback2').innerHTML = 'Correct!';
            text_box.style.backgroundColor = 'green';
        }
        else {
            document.querySelector('#feedback2').innerHTML = 'Incorrect!';
            text_box.style.backgroundColor = 'Red';
        }
    });
});