# Repository Configuration

This directory contains GitHub-specific configuration files for the 8085 Emulator repository.

## Contents

### Workflows (`.github/workflows/`)

Automated CI/CD workflows that run on pull requests and pushes:

1. **build-and-test.yml** - Builds the project with both Make and CMake
   - Installs Qt5 dependencies
   - Verifies build succeeds
   - Job name: `build`

2. **code-quality.yml** - Performs basic code quality checks
   - Validates required files exist
   - Checks for common issues
   - Job name: `check-files`

### Branch Protection Documentation

1. **BRANCH_PROTECTION_SETUP.md** - Step-by-step guide to configure branch protection
   - Quick setup instructions
   - Screenshots and examples
   - Troubleshooting tips

2. **branch-protection-config.json** - Reference configuration
   - JSON representation of recommended settings
   - Useful for documentation and review
   - Not automatically applied (manual configuration required)

## Setting Up Branch Protection

Branch protection rules must be configured manually through the GitHub web interface by a repository administrator.

**Quick Start:**
1. Read [BRANCH_PROTECTION_SETUP.md](BRANCH_PROTECTION_SETUP.md)
2. Go to repository Settings → Branches
3. Add protection rule for `main` branch
4. Enable recommended settings

**Full Documentation:**
- See [../BRANCH_PROTECTION.md](../BRANCH_PROTECTION.md) for detailed explanations

## GitHub Actions Status Checks

The workflows in this directory will:
- Run automatically on pull requests to `main`
- Run automatically on pushes to `main`
- Provide status checks that can be required before merging

After the first workflow run, you can require these status checks in branch protection settings:
- `build` - Ensures code compiles
- `check-files` - Ensures repository structure is correct

## Maintenance

### Adding New Workflows
1. Create new `.yml` file in `workflows/` directory
2. Follow GitHub Actions syntax
3. Test with a pull request
4. Update this README

### Modifying Branch Protection
1. Edit in Settings → Branches (requires admin)
2. Update documentation if changing recommendations
3. Notify team of changes

## Support

For questions about:
- **Workflows**: Check workflow logs in Actions tab
- **Branch Protection**: See BRANCH_PROTECTION_SETUP.md
- **Configuration**: Contact repository administrator
