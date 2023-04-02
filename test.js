const {save_file, open_file, message, notify} = require('./portableDialogsJs');

console.log('Notify response', notify("Notification", "This is an info notification", "info"));
console.log('Message response', message("Message", "This is an info message", "info"));
console.log('File to save', save_file('Alabama3.m3u'));
console.log('File to open', open_file());