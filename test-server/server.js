const express = require('express')
const app = express()
const PORT = 3000
app.use(express.json())
app.use(express.text())
const words = [
    'is a poop',
    'is george michael',
    'in makers',
    'wants boba',
    'is imposter',
    'is still on fire',
    'is not gandhi',
    'is dying in csci104',
    'takes ee109',
    'is SCandalous',
    'likes j a z z',
]
let latest = 'nothing here yet... send a post request!'
app.get('/', (req, res) => {
    res.send(latest)
})
app.get('/json', (req, res) => {
    res.json({ message: latest })
})
app.post('/', (req, res) => {
    if (!req.body) {
        res.status(400)
        return res.send('y no data')
    }
    const temp =
        req.body + ' ' + words[Math.floor(Math.random() * words.length)]
    latest = temp
    res.send(temp)
})
app.post('/json', (req, res) => {
    if (!req.body.message) {
        res.status(400)
        return res.json({ message: 'y no data' })
    }
    const temp =
        req.body.message + ' ' + words[Math.floor(Math.random() * words.length)]
    latest = temp
    res.json({ message: temp })
})
app.put('/', (req, res) => {
    res.send('OK!')
})
app.listen(PORT, () => console.log('Running on port ', PORT))
