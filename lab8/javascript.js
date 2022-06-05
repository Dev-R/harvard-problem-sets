    document.addEventListener('DOMContentLoaded', function()
    {
        const CORRECT = "<span style ='color : green;' >Correct ! ✔ </span>";
        const INCORRECT = "<span style = 'color : red;' > Incorrect ! 👎</span>"
        // Hightlight Q1 correct answer
        let correct = document.querySelector(".correct");
        correct.addEventListener('click', function()
        {
            correct.style.backgroundColor = 'green';
            document.querySelector('#feedback1').innerHTML = CORRECT;
        }
        );
        
        // Hightlight Q1 incorrect answer
        let incorrects = document.querySelectorAll(".incorrect");
            for(let i = 0; i < incorrects.length; i++)
            {
                incorrects[i].addEventListener('click', function()
                {
                    incorrects[i].style.backgroundColor = 'red';
                    document.querySelector('#feedback1').innerHTML = INCORRECT;
                }
                );

                //document.querySelector('#feedback1').innerHTML = "<span style = 'color : red;' > Incorrect ! 👎</span>";
            }
        
        //Highlight Q2 answer
        let answer = document.querySelector("#submit");
        answer.addEventListener('click', function()
        {
            let input = document.querySelector("#q2_ans");
            if(input.value === 'CS106 Stanford')
            {
                //document.getElementById('feedback2')style.backgroundColor = 'green';
                input.style.backgroundColor = 'green';
                document.querySelector('#feedback2').innerHTML = CORRECT;
            }
            else
            {
                input.style.backgroundColor = 'red';
                document.querySelector('#feedback2').innerHTML = INCORRECT;
            }
        });
        
    });