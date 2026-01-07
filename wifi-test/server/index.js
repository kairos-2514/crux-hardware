const express = require('express');
const bodyParser = require('body-parser');
const app = express();
const port = 3000;

// Middleware to parse JSON bodies
app.use(bodyParser.json());
// Middleware to parse URL-encoded bodies
app.use(bodyParser.urlencoded({ extended: true }));

// GET endpoint for simple testing
app.get('/', (req, res) => {
  res.send('Server is running!');
});

// POST endpoint to receive message
app.post('/message', (req, res) => {
  console.log('Received message:', req.body);
  res.send('Message received');
});

// GET endpoint to receive message via query params (easier for simple browser/arduino tests)
app.get('/message', (req, res) => {
    console.log('Received message query:', req.query);
    res.send('Message received');
});

app.listen(port, '0.0.0.0', () => {
  console.log(`Server listening at http://0.0.0.0:${port}`);
  console.log(`Ensure your ESP32 uses your computer's local IP address, not localhost!`);
});
