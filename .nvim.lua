vim.notify("AVS-UI .nvim.lua loaded!", vim.log.levels.INFO)

-- layout
require('nvim-tree.api').tree.open()

-- vim.schedule(function()
--	require('toggleterm').toggle(nil, nil, nil, 'horizontal')
-- end)

-- Editor basics
vim.opt_local.tabstop = 4
vim.opt_local.shiftwidth = 4
vim.opt_local.expandtab = false

-- Project setup
vim.g.avs_project_name = 'avs-ui'


vim.api.nvim_create_user_command( 'avs_run', function() 
	vim.cmd('!make run')
end, {})


