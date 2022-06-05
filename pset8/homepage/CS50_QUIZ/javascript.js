document.addEventListener('DOMContentLoaded', function()
{
    const CORRECT = "<span style = 'color:green;'> Correct😎</span>";
    const INCORRECT = "<span style = 'color:red;'> Incorrect😒</span>";
    let answer = document.querySelectorAll('.submit');
    for (let i = 0; i < answer.length; i++)
    {
        let input = document.querySelector("#check1");
        let input2 = document.querySelector("#check2");
        answer[i].addEventListener('click', function()
        {
            if(input.value === '2006')
        {
            input.backgroundColor = 'green';
            document.querySelector("#feedback1").innerHTML = CORRECT;
        }
                else
        {
            input.backgroundColor = 'red';
            document.querySelector("#feedback1").innerHTML = INCORRECT;
        }
        
        
        if (input2.value === 'Harvard' && input2.value.length != 0)
        {
            input2.backgroundColor = 'green';
            document.querySelector("#feedback2").innerHTML = CORRECT;
        }
        else if (input2.value != 'Harvard' && input2.value.length != 0)
        {
            input2.backgroundColor = 'red';
            document.querySelector("#feedback2").innerHTML = INCORRECT;
        }
        });
    }
});