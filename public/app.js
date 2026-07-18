const canvas = document.getElementById("game");
const ctx = canvas.getContext("2d");

const WIDTH = canvas.width;
const HEIGHT = canvas.height;

const bird = {
    x: 100,
    y: HEIGHT / 2,
    radius: 20,
    velocity: 0
};

const gravity = 0.5;
const flap = -8;

let pipes = [];
let score = 0;
let gameOver = false;

function addPipe() {
    const gap = 180;
    const topHeight = Math.random() * 250 + 50;

    pipes.push({
        x: WIDTH,
        top: topHeight,
        bottom: topHeight + gap,
        passed: false
    });
}

setInterval(() => {
    if (!gameOver)
        addPipe();
}, 1800);

function restart() {
    bird.y = HEIGHT / 2;
    bird.velocity = 0;
    pipes = [];
    score = 0;
    gameOver = false;
}

function jump() {
    if (gameOver) {
        restart();
        return;
    }

    bird.velocity = flap;
}

document.addEventListener("keydown", e => {
    if (e.code === "Space")
        jump();
});

canvas.addEventListener("click", jump);
canvas.addEventListener("touchstart", e => {
    e.preventDefault();
    jump();
});

function update() {
    if (gameOver)
        return;

    bird.velocity += gravity;
    bird.y += bird.velocity;

    for (let pipe of pipes) {
        pipe.x -= 3;

        if (!pipe.passed && pipe.x + 60 < bird.x) {
            pipe.passed = true;
            score++;
        }

        const hitX =
            bird.x + bird.radius > pipe.x &&
            bird.x - bird.radius < pipe.x + 60;

        const hitY =
            bird.y - bird.radius < pipe.top ||
            bird.y + bird.radius > pipe.bottom;

        if (hitX && hitY)
            gameOver = true;
    }

    pipes = pipes.filter(pipe => pipe.x > -60);

    if (
        bird.y + bird.radius > HEIGHT ||
        bird.y - bird.radius < 0
    ) {
        gameOver = true;
    }
}

function draw() {
    ctx.clearRect(0, 0, WIDTH, HEIGHT);

    // pipes
    ctx.fillStyle = "green";

    for (let pipe of pipes) {
        ctx.fillRect(pipe.x, 0, 60, pipe.top);

        ctx.fillRect(
            pipe.x,
            pipe.bottom,
            60,
            HEIGHT - pipe.bottom
        );
    }

    // bird
    ctx.fillStyle = "yellow";

    ctx.beginPath();
    ctx.arc(
        bird.x,
        bird.y,
        bird.radius,
        0,
        Math.PI * 2
    );
    ctx.fill();

    // score
    ctx.fillStyle = "black";
    ctx.font = "30px Arial";
    ctx.fillText(`Score: ${score}`, 20, 40);

    if (gameOver) {
        ctx.font = "40px Arial";
        ctx.fillText("Game Over", 80, 250);

        ctx.font = "20px Arial";
        ctx.fillText(
            "Press Space or Tap to Restart",
            45,
            300
        );
    }
}

function loop() {
    update();
    draw();
    requestAnimationFrame(loop);
}

loop();