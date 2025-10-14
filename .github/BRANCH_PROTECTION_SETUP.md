# Quick Setup Guide for Branch Protection

This guide will help you quickly set up branch protection rules for the `main` branch.

## Step-by-Step Setup

### 1. Navigate to Branch Protection Settings

Go to: https://github.com/PrashunKC/8085_emulation/settings/branches

Or manually:
1. Click on "Settings" tab in your repository
2. Click on "Branches" in the left sidebar
3. Click "Add branch protection rule" button

### 2. Configure Branch Name Pattern

Enter: `main`

This will apply the rules to the main branch.

### 3. Enable Protection Settings

Check the following boxes:

#### ✅ Require a pull request before merging
- ✅ Require approvals: Set to **1** (or higher)
- ✅ Dismiss stale pull request approvals when new commits are pushed
- ✅ Require review from Code Owners (optional, if CODEOWNERS file exists)

#### ✅ Require status checks to pass before merging
Once the GitHub Actions workflows start running, you can require:
- `build` (from build-and-test.yml)
- `check-files` (from code-quality.yml)

Options to check:
- ✅ Require branches to be up to date before merging

#### ✅ Require conversation resolution before merging
Ensures all review comments are addressed

#### ✅ Do not allow bypassing the above settings
Ensures rules apply to everyone, including administrators

#### ✅ Do not allow force pushes
**Critical**: Prevents rewriting git history

#### ✅ Do not allow deletions
**Critical**: Prevents accidental deletion of the main branch

### 4. Save the Rule

Click the "Create" button at the bottom of the page.

## Verification

After setup, try to:
1. Force push to main (should be blocked)
2. Delete main branch (should be blocked)
3. Push directly to main without PR (should be blocked if PR requirement enabled)

## Status Checks

The repository now includes two GitHub Actions workflows:

1. **Build and Test** (`build-and-test.yml`)
   - Verifies code builds with both Make and CMake
   - Requires Qt5 dependencies
   - Runs on every PR and push to main

2. **Code Quality Checks** (`code-quality.yml`)
   - Checks for required files
   - Validates file structure
   - Runs basic quality checks
   - Runs on every PR and push to main

These workflows will automatically run on pull requests and can be required as status checks.

## Testing the Setup

Create a test branch and PR to verify:
```bash
git checkout -b test-branch-protection
echo "Test" >> README.md
git add README.md
git commit -m "Test branch protection"
git push origin test-branch-protection
```

Then create a PR from the GitHub web interface and observe:
- Status checks running automatically
- Merge button disabled until checks pass
- Force push attempts blocked

## Troubleshooting

### Status checks not appearing?
- Wait for first workflow run to complete
- Refresh the branch protection settings page
- The workflow names should appear in the status checks list

### Can't find the settings?
- You need admin permissions on the repository
- Contact repository owner if you don't have access

### Want to modify the rules?
- Edit the rule from Settings → Branches
- Click the pencil icon next to the rule name

## More Information

For detailed information about why each setting is important, see [BRANCH_PROTECTION.md](../BRANCH_PROTECTION.md) in the root of the repository.

## Support

If you need help:
1. Check the GitHub documentation: https://docs.github.com/en/repositories/configuring-branches-and-merges-in-your-repository/managing-protected-branches
2. Review the BRANCH_PROTECTION.md documentation
3. Contact the repository administrator
