
const source=document.querySelector('#code');
if(source){
 document.querySelector('#section').textContent=document.querySelector('#section').textContent.replaceAll('_',' ');
 const key='source:'+location.search;
 if(!source.value)source.value=sessionStorage.getItem(key)||'';
 source.oninput=()=>sessionStorage.setItem(key,source.value);
 document.querySelector('#file').onchange=async e=>{const f=e.target.files[0];if(f&&(!source.value||confirm('Replace the current source?'))){source.value=await f.text();source.dispatchEvent(new Event("input"));}};
}
const builder=document.querySelector('#builder');
for(const form of document.forms)form.onsubmit=()=>{const button=form.querySelector('button[type=submit]');button.disabled=true;button.textContent='Working…';};

for (const box of document.querySelectorAll('#code, textarea[name=solution], textarea[name=generator]')) {
 let escapeTab=false;
 box.addEventListener('keydown',event=>{
  if(event.key==='Escape'){escapeTab=true;return;}
  if(event.key!=='Tab'||escapeTab){escapeTab=false;return;}
  event.preventDefault();
  const value=box.value,start=box.selectionStart,end=box.selectionEnd;
  if(!event.shiftKey && start===end){
   box.setRangeText('    ',start,end,'end');
  }else{
   const first=value.slice(0,start).lastIndexOf('\n')+1;
   const last=end>start && value[end-1]==='\n'?end-1:end;
   const lines=value.slice(first,last).split('\n');
   const indent=line=>event.shiftKey?line.replace(/^( {1,4}|\t)/,''):'    '+line;
   const changed=lines.map(indent).join('\n');
   box.setRangeText(changed,first,last,'preserve');
   const delta=indent(lines[0]).length-lines[0].length;
   box.setSelectionRange(Math.max(first,start+delta),end+changed.length-(last-first));
  }
  box.dispatchEvent(new Event('input',{bubbles:true}));
 });
}
const statement=document.querySelector('#statement');
if(statement){
 const paragraphs=statement.textContent.split(/\n\s*\n/);
 statement.replaceChildren();
 for(const part of paragraphs){
  const lines=part.split('\n');
  if(lines.length>1 && ['Input','Output','Constraints'].includes(lines[0])){
   const heading=document.createElement('h2');heading.textContent=lines.shift();statement.append(heading);
  }
  const p=document.createElement('p');p.textContent=lines.join('\n');statement.append(p);
 }
}
if (builder) {
 const addCase = (type) => {
  const sample = type === 'samples';
  const group = document.createElement('div');
  group.className = 'case';
  const fields = document.createElement('div');
  if (sample) fields.className = 'pair';
  for (const [name,title] of sample ? [['input','Sample input'],['output','Expected sample output']] : [['hidden','Manual hidden input']]) {
   const label = document.createElement('label');
   const box = document.createElement('textarea');
   box.name = name;
   label.append(title,box);
   fields.append(label);
  }
  const remove = document.createElement('button');
  remove.type = 'button';
  remove.dataset.remove = '';
  remove.textContent = sample ? 'Remove sample' : 'Remove hidden case';
  group.append(fields,remove);
  document.getElementById(type).append(group);
  return fields.querySelector('textarea');
 };
 builder.addEventListener('click', event => {
  const button = event.target.closest('button');
  if (!button) return;
  if (button.dataset.add) addCase(button.dataset.add).focus();
  if (button.hasAttribute('data-remove')) button.closest('.case').remove();
  if(button.dataset.add||button.hasAttribute('data-remove')) builder.dispatchEvent(new Event('input'));
 });
 if (!document.querySelector('#samples .case') && !location.search && !document.querySelector('[role=alert]')) addCase('samples');
 const draftKey='builder-v2:'+location.search;
 const revision=builder.elements.revision.value;
 let draft;
 try {draft=JSON.parse(sessionStorage.getItem(draftKey));} catch {}
 if(draft && draft.revision===revision && !document.querySelector('[role=alert]')){
  for(const type of ['samples','hidden'])document.getElementById(type).replaceChildren();
  for(const _ of draft.fields.input||[])addCase('samples');
  for(const _ of draft.fields.hidden||[])addCase('hidden');
  const offset={};
  for(const field of builder.elements){
   if(!field.name || field.name==='revision')continue;
   const index=offset[field.name]||0;
   if(draft.fields[field.name]?.[index]!==undefined)field.value=draft.fields[field.name][index];
   offset[field.name]=index+1;
  }
 }
 builder.addEventListener('input',()=>{
  const fields={};
  for(const [key,value] of new FormData(builder))(fields[key]??=[]).push(value);
  try{sessionStorage.setItem(draftKey,JSON.stringify({revision,fields}));}catch{}
 });
}
// Keep the native textarea for selection, IME, file import and keyboard editing.
function highlight(text) {
 return Prism.highlight(text, Prism.languages.cpp, 'cpp');
}
for (const box of document.querySelectorAll('#code,textarea[name=solution],textarea[name=generator]')) {
 const shell=document.createElement('div');
 shell.className='code-editor';
 const mirror=document.createElement('pre');
 mirror.setAttribute('aria-hidden','true');
 box.before(shell);
 shell.append(mirror,box);
 box.wrap='off';
 box.spellcheck=false;
 const sync=()=>{
  mirror.style.width=box.clientWidth+'px';
  mirror.style.height=box.clientHeight+'px';
  mirror.scrollLeft=box.scrollLeft;
  mirror.scrollTop=box.scrollTop;
 };
 const paint=()=>{mirror.innerHTML=highlight(box.value)+'\n';sync();};
 box.addEventListener('input',paint);
 box.addEventListener('scroll',sync);
 new ResizeObserver(sync).observe(box);
 paint();
}
const editorial=document.querySelector('#editorial');
if(editorial){
 const lines=editorial.textContent.split(/\r?\n/);
 editorial.replaceChildren();
 let block=[],code=false;
 function flush(){
  if(!block.length)return;
  const element=document.createElement(code?'pre':'p');
  const value=block.join('\n');
  if(code)element.innerHTML=highlight(value);
  else element.textContent=value;
  editorial.append(element);
  block=[];
 }
 for(const line of lines){
  if(line.trim()==='~~~'){flush();code=!code;}
  else if(!code&&!line.trim())flush();
  else block.push(line);
 }
 flush();
}
