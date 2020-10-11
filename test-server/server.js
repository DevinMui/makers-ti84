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

// i'm lazy

let names = []
// {
//   to
//   from
//   msg
// }
let messages = []

app.get('/names', (req, res) => {
    res.json({ names: names })
})

app.post('/names', (req, res) => {
    names.push(req.body.name)
    res.json({ names: names })
})

app.get('/d_msg', (req, res) => {
    res.json(messages)
})

app.get('/messages', (req, res) => {
    const from = req.query.from
    const to = req.query.to
    const filtered_msgs = messages.filter((message) => {
        if (message.from === from && message.to === to) return message
    })
    let msgs = filtered_msgs
    // const cutoff_length = 3
    // if (msgs.length > cutoff_length)
    //     msgs = filtered_msgs.slice(msgs.length - cutoff_length, msgs.length)
    res.json(msgs[msgs.length - 1] || {})
})

app.post('/messages', (req, res) => {
    const payload = {
        from: req.body.from || 'Anon',
        to: req.body.to || 'Anon',
        msg: req.body.msg || '',
    }
    messages.push(payload)
    res.json(payload)
})

app.listen(PORT, () => console.log('Running on port ', PORT))
