const fs = require('fs');

const input = fs.readFileSync('input.txt', 'utf8').trim().split('\n').slice(2);
const grid = input.map(line => {
    const [, x, y, size, used, avail] = line.match(/node-x(\d+)-y(\d+)\s+(\d+)T\s+(\d+)T\s+(\d+)T\s+/).map(Number);
    return { x, y, size, used, avail };
});

const width = Math.max(...grid.map(node => node.x)) + 1;
const height = Math.max(...grid.map(node => node.y)) + 1;
const emptyNode = grid.find(node => node.used === 0);
const goalNode = { x: width - 1, y: 0 };

const grid2D = Array.from({ length: height }, () => Array(width).fill(null));
grid.forEach(node => {
    grid2D[node.y][node.x] = {
        used: node.used,
        avail: node.avail,
        size: node.size
    };
});

const directions = [
    { x: 1, y: 0 },
    { x: -1, y: 0 },
    { x: 0, y: 1 },
    { x: 0, y: -1 }
];

const bfs = (start, goal) => {
    const queue = [[start]];
    const visited = new Set([`${start.x},${start.y}`]);

    while (queue.length > 0) {
        const path = queue.shift();
        const { x, y } = path[path.length - 1];

        if (x === goal.x && y === goal.y) {
            return path;
        }

        for (const dir of directions) {
            const nx = x + dir.x;
            const ny = y + dir.y;

            if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                const key = `${nx},${ny}`;
                const node = grid2D[ny][nx];

                if (!visited.has(key) && node && node.used <= emptyNode.size) {
                    visited.add(key);
                    queue.push([...path, { x: nx, y: ny }]);
                }
            }
        }
    }
    return [];
};

const moveEmptyNodeToNeighborOfGoal = () => {
    const target = {
        x: goalNode.x - 1,
        y: goalNode.y
    };

    const path = bfs(emptyNode, target);
    if (path.length === 0) {
        throw new Error("No valid path found!");
    }

    return path.length - 1;
};

const moveGoalDataToTopLeft = (stepsToMoveEmpty) => {
    let steps = 1;

    const goalPath = goalNode.x - 1;
    steps += goalPath * 5;

    return stepsToMoveEmpty + steps;
};

try {
    const stepsToMoveEmpty = moveEmptyNodeToNeighborOfGoal();
    const totalSteps = moveGoalDataToTopLeft(stepsToMoveEmpty);

    console.log(`Fewest number of steps required: ${totalSteps}`);
} catch (error) {
    console.error(error.message);
}
