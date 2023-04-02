const pdjs = require('bindings')('addon_pdjs.node');

function iconCheck(type) { if(! ['info', 'question', 'warning', 'error'].includes(type)) throw(`error: bad type: ${type}`);}

function save_file(name='') { return pdjs.save_file(name); };
function open_file(name = process.env.HOME) { return pdjs.open_file(name); };
function message(title, msg, type) { iconCheck(type); return pdjs.message(title, msg, type); }
function notify(title, msg, type) { iconCheck(type); return pdjs.notify(title, msg, type); }

module.exports = {save_file, open_file, message, notify};
